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
#include "../../../include/libs-klipos.h"


//----------------------------- private functions & defines

#define ADC_CR_CLKDIV_MASK      (0xFF << 0)	/*!< Mask for Clock divider value */
#define ADC_CR_CLKDIV_BITPOS    (0)		/*!< Bit position for Clock divider value */
#define ADC_CR_ASYNMODE         (1 << 8)	/*!< Asynchronous mode enable bit */
#define ADC_CR_MODE10BIT        (1 << 9)	/*!< 10-bit mode enable bit */
#define ADC_CR_LPWRMODEBIT      (1 << 10)	/*!< Low power mode enable bit */
#define ADC_CR_CALMODEBIT       (1 << 30)	/*!< Self calibration cycle enable bit */

/** Maximum sample rate in Hz (12-bit conversions) */
//#define ADC_MAX_SAMPLE_RATE     50000000


void setAnalogClock(LPC_ADC_T *pADC, uint32_t rateInKHz)
{
    uint32_t temp;
    
    uint32_t div = KERNEL_CPU_FREQ / rateInKHz;
    if (div==0)
    {
        div = 1;
    }
    
    div = div - 1;
    
    temp = pADC->CTRL & ~(ADC_CR_CLKDIV_MASK);
    pADC->CTRL = temp | (uint32_t) div;
}


void startAnalogCalibration(LPC_ADC_T *pADC)
{
    uint32_t backup = pADC->CTRL;
    
    /* Set calibration mode */
    pADC->CTRL |= ADC_CR_CALMODEBIT;

    /* Clear ASYNC bit */
    pADC->CTRL &= ~ADC_CR_ASYNMODE;

    /* Setup ADC for about 500KHz (per UM) */
    setAnalogClock(pADC, 500);

    /* Clear low power bit */
    pADC->CTRL &= ~ADC_CR_LPWRMODEBIT;

    /* Calibration is only complete when ADC_CR_CALMODEBIT bit has cleared */
    while((pADC->CTRL & ADC_CR_CALMODEBIT) != 0)
    {
        
    }

    pADC->CTRL = backup;
}

//----------------------------- public functions

void initAnalog(uint32_t analogChannel)
{
    // enable clock for adc block
    SETBIT(LPC_SYSCON->SYSAHBCLKCTRL[0], 27);

    // clear reset for adc
    SETBIT(LPC_SYSCON->PRESETCTRL[0], 27);
    CLRBIT(LPC_SYSCON->PRESETCTRL[0], 27);

//    SETBIT(LPC_SYSCON->SYSAHBCLKCTRL[0], 28);
//    CLRBIT(LPC_SYSCON->PRESETCTRL[0], 28);
    
    if( (analogChannel & ANA0) == ANA0)
    {
        enableFixedFunction(SWM_FIXED_ADC0_0, true);
    }
    
    if( (analogChannel & ANA1) == ANA1)
    {
        enableFixedFunction(SWM_FIXED_ADC0_1, true);
    }
    
    if( (analogChannel & ANA2) == ANA2)
    {
        enableFixedFunction(SWM_FIXED_ADC0_2, true);
    }
    
    if( (analogChannel & ANA3) == ANA3)
    {
        enableFixedFunction(SWM_FIXED_ADC0_3, true);
    }
    
    if( (analogChannel & ANA4) == ANA4)
    {
        enableFixedFunction(SWM_FIXED_ADC0_4, true);
    }
    
    if( (analogChannel & ANA5) == ANA5)
    {
        enableFixedFunction(SWM_FIXED_ADC0_5, true);
    }
    
    if( (analogChannel & ANA6) == ANA6)
    {
        enableFixedFunction(SWM_FIXED_ADC0_6, true);
    }
    
    if( (analogChannel & ANA7) == ANA7)
    {
        enableFixedFunction(SWM_FIXED_ADC0_7, true);
    }
    
    // power on adc
    CLRBIT(LPC_SYSCON->PDRUNCFG, 10);
  
    LPC_ADC0->INTEN = 0;
    LPC_ADC0->CTRL = 0; // normal mode 12 bits
    
    startAnalogCalibration(LPC_ADC0);
    
    // set clock to 36 MHz
    LPC_ADC0->CTRL = 1;
    
    
//    CLRBIT(LPC_SYSCON->PDRUNCFG, 11);
}

uint16_t getAnalog(ANALOG_CHANNEL channel)
{
    uint32_t temp;
    uint16_t result;

    // disable convertion channel
    CLRBIT(LPC_ADC0->SEQ_CTRL[0], 31);
    
    // clear previous channel
    CLRBITS(LPC_ADC0->SEQ_CTRL[0],0xFFF);  
    
    LPC_ADC0->SEQ_CTRL[0] |= channel;
    
    SETBIT(LPC_ADC0->SEQ_CTRL[0], 18);
    SETBIT(LPC_ADC0->SEQ_CTRL[0], 28);
    
    SETBIT(LPC_ADC0->SEQ_CTRL[0], 31);
    
    // launch adc
    SETBIT(LPC_ADC0->SEQ_CTRL[0], 26);
    
    temp = LPC_ADC0->SEQ_GDAT[0];
    
    while ( (temp & BIT(31)) == 0 )
    {
        temp = LPC_ADC0->SEQ_GDAT[0];
    }
    
    result = (temp >> 4) & 0x0FFF;
    
    return result;
}
