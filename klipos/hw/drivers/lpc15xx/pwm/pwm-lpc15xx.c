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

#define SCT_FREQUENCY_KHZ       12000

#define SCT_0_INDEX              0
#define SCT_1_INDEX              2
#define SCT_2_INDEX              4
#define SCT_3_INDEX              6


#define GET_PWM_TICK(timeInUs) ((SCT_FREQUENCY_KHZ/1000)*(timeInUs) -1)



//------------------------ public functions

void initPwm(Pwm *pwm, 
        PWMTIMER timerType, PWMOUTPUT pwmSelected, 
        uint32_t widthInUs, 
        uint32_t widthDivider, 
        uint32_t percentage)
{
    uint32_t ticks;
    uint32_t dutyCycle;
    
    uint32_t evt;
    LPC_SCT_T * sct = LPC_SCT0;
    
    switch(timerType)
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
    
    evt = pwmSelected *2;
    
    pwm->evt = evt;
    pwm->sct = sct;
    
    sct->CONFIG |= BIT(17);
    
    // SCT frequency set to 12 MHz
    sct->CTRL_U |= BITS(5,5);
    sct->CTRL_U |= BITS(21,5);
 
    
    ticks = GET_PWM_TICK(widthInUs);
    
    dutyCycle = (ticks * percentage) / 1000;
    
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
}

void setPwmDutyCycle(Pwm *pwm, uint32_t percentage)
{
    uint32_t ticks = pwm->sct->MATCHREL[pwm->evt].L;
    uint32_t dutyCycle = (ticks * percentage) / 1000;
    
    pwm->sct->MATCHREL[pwm->evt+1].L = dutyCycle;
}

void setPwmWidth(Pwm *pwm, uint32_t widthInUs)
{
    uint32_t ticks = GET_PWM_TICK(widthInUs);
    
    pwm->sct->MATCHREL[pwm->evt].L= ticks;
}
