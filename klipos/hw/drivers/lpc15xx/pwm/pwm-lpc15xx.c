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
#include "../../../include/libs-klipos.h"

#define DEFAULT_SCT_PRESCALER    5
#define DEFAULT_FREQUENCY_KHZ    12000

#define GET_PWM_TICK(timeInUs, freq) (((freq)/1000)*(timeInUs))



//------------------------ public functions


uint32_t computePwmPrescalerFromClock(uint32_t pwmClockInKHz)
{
    uint32_t prescaler = KERNEL_CPU_FREQ / pwmClockInKHz;
    
    if (prescaler > 255)
    {
        return 0;
    }
    else if (prescaler == 0)
    {
        return 0;
    }
    
    prescaler = prescaler-1;
    
    return prescaler;
}

void initPwm(Pwm * pwm, PWM_SCT sctPwm, uint32_t prescaler)
{
    LPC_SCT_T * sct = LPC_SCT0;
    
    switch(sctPwm)
    {
        case PWM_SCT0:
            sct = LPC_SCT0;
            SETBIT(LPC_SYSCON->SYSAHBCLKCTRL[1],2);
            
            SETBIT(LPC_SYSCON->PRESETCTRL[1], 2);
            CLRBIT(LPC_SYSCON->PRESETCTRL[1], 2);
            break;
        case PWM_SCT1:
            sct = LPC_SCT1;
            SETBIT(LPC_SYSCON->SYSAHBCLKCTRL[1],3);
            
            SETBIT(LPC_SYSCON->PRESETCTRL[1], 3);
            CLRBIT(LPC_SYSCON->PRESETCTRL[1], 3);
            break;
        case PWM_SCT2:
            sct = LPC_SCT2;
            SETBIT(LPC_SYSCON->SYSAHBCLKCTRL[1],4);

            SETBIT(LPC_SYSCON->PRESETCTRL[1], 4);
            CLRBIT(LPC_SYSCON->PRESETCTRL[1], 4);
            break;
        case PWM_SCT3:
            sct = LPC_SCT3;
            SETBIT(LPC_SYSCON->SYSAHBCLKCTRL[1],5);
            
            SETBIT(LPC_SYSCON->PRESETCTRL[1], 5);
            CLRBIT(LPC_SYSCON->PRESETCTRL[1], 5);
            break;
    }
    
    sct->CONFIG |= BIT(17);
    
    uint32_t frequency;
    if (prescaler==0)
    {
        prescaler = DEFAULT_SCT_PRESCALER;
        frequency = DEFAULT_FREQUENCY_KHZ;
    }
    
    pwm->sct = sct;
    pwm->freq = KERNEL_CPU_FREQ / (prescaler+1);
     
    sct->CTRL_U |= BITS(5,prescaler);
    sct->CTRL_U |= BITS(21,prescaler);
}

void clonePwm(Pwm *from, Pwm *to)
{
    to->sct = from->sct;
    to->freq = from->freq;
}

void setPwmOutput(Pwm *pwm, PWM_OUTPUT pwmSelected, 
        uint32_t widthInUs, uint32_t percentage)
{
    uint32_t ticks;
    uint32_t dutyCycle;
    
    uint32_t evt = pwmSelected * 2;
    LPC_SCT_T * sct = pwm->sct;
    uint32_t frequency = pwm->freq;
    
    pwm->evt = evt;
    
    ticks = GET_PWM_TICK(widthInUs, frequency);    
    dutyCycle = (ticks * percentage) / 1000;
    
    sct->MATCH[evt].L=0;
    
    sct->MATCHREL[evt].L= ticks;
    sct->MATCHREL[evt+1].L = dutyCycle;
    
    sct->EVENT[evt].STATE = 0xFFFFFFFF;
    sct->EVENT[evt].CTRL = (evt) | (1 << 12);
    
    sct->EVENT[evt+1].STATE = 0xFFFFFFFF;
    sct->EVENT[evt+1].CTRL = (evt+1) | (1 << 12);
    
    sct->OUT[pwmSelected].SET = (1 << (evt));
    sct->OUT[pwmSelected].CLR = (1 << (evt+1));
}


void enablePwm(Pwm *pwm)
{
    CLRBIT(pwm->sct->CTRL_U, 2); 
    CLRBIT(pwm->sct->CTRL_U, 18);
}

void disablePwm(Pwm *pwm)
{
    SETBIT(pwm->sct->CTRL_U, 2); 
    SETBIT(pwm->sct->CTRL_U, 18);
    
    SETBIT(pwm->sct->CTRL_U, 3);
    SETBIT(pwm->sct->CTRL_U, 19);
    
    pwm->sct->COUNT_L = 0;
    pwm->sct->COUNT_H = 0;
}

void setPwmDutyCycle(Pwm *pwm, uint32_t percentage)
{
    uint32_t ticks = pwm->sct->MATCHREL[pwm->evt].L;
    uint32_t dutyCycle = (ticks * percentage) / 1000;
    
    pwm->sct->MATCHREL[pwm->evt+1].L = dutyCycle;
}

void setPwmWidth(Pwm *pwm, uint32_t widthInUs)
{
    uint32_t ticks = GET_PWM_TICK(widthInUs, pwm->freq);
    
    pwm->sct->MATCH[pwm->evt].L=0;
    pwm->sct->MATCHREL[pwm->evt].L= ticks;
}
