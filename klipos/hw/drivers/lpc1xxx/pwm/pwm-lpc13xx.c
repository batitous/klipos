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


//-------------------------- private variables:


static volatile UInt8 pwm_stopped;


//-------------------------- private functions:


void Timer_Handler(LPC_TMR_TypeDef *timer)
{
    // Acknoledge interrupt
    SETBIT(timer->IR,3);
    
    // Disable timer and reset counter
    timer->TCR = 0x2;
    
    // Disable interrupt
    CLRBIT(timer->MCR,9);
    
    pwm_stopped = 1;
}

void TIMER_16_0_IRQn_Handler(void)
{
    Timer_Handler(LPC_TMR16B0);
}

void TIMER_16_1_IRQn_Handler(void)
{
    Timer_Handler(LPC_TMR16B1);
}

/* TODO
void TIMER_32_0_IRQn_Handler(void)
{
    Timer_Handler(LPC_TMR32B0);
}

void TIMER_32_1_IRQn_Handler(void)
{
    Timer_Handler(LPC_TMR32B1);
}*/



void setPwmPin(PWMTIMER timerSelected, PWMOUTPUT pwmSelected)
{
    // IOCON_R_PIO0_11 CT32B0_MAT3 warning : AD0 FUNC=0x3
    // IOCON_R_PIO1_0 CT32B1_CAP0 warning : AD1 FUNC=0x3
    // IOCON_PIO1_4 CT32B1_MAT3 warning: AD5 FUNC=0x2
    // IOCON_PIO1_5 CT32B0_CAP0 FUNC=0x2
    
    if(timerSelected==TIMER32_0)
    {
        if( (pwmSelected&PWM0)==PWM0)
        {
            // not activated!

            // IOCON_PIO1_6 CT32B0_MAT0 warning: RXD FUNC=0x2
            //SETBIT(LPC_IOCON->PIO1_6,1);
        }

        if( (pwmSelected&PWM1)==PWM1)
        {
            // not activated!

            // IOCON_PIO1_7 CT32B0_MAT1 warning: TXD FUNC=0x2
            //SETBIT(LPC_IOCON->PIO1_7,1);
        }

        if( (pwmSelected&PWM2)==PWM2)
        {
            // IOCON_PIO0_1 CT32B0_MAT2 FUNC=0x2
            SETBIT(LPC_IOCON->PIO0_1,1);
        }
    }
    else if (timerSelected==TIMER32_1)
    {
        if( (pwmSelected&PWM0)==PWM0)
        {
            // IOCON_R_PIO1_1 CT32B1_MAT0 warning : AD2 FUNC=0x3
        #ifdef MCU_IS_LPC1311
            SETBIT(LPC_IOCON->R_PIO1_1,0);
            SETBIT(LPC_IOCON->R_PIO1_1,1);
        #endif
        }

        if( (pwmSelected&PWM1)==PWM1)
        {
            // IOCON_R_PIO1_2 CT32B1_MAT1 warning : AD3 FUNC=0x3
        #ifdef MCU_IS_LPC1311
            SETBIT(LPC_IOCON->R_PIO1_2,0);
            SETBIT(LPC_IOCON->R_PIO1_2,1);
        #endif
        }

        if( (pwmSelected&PWM2)==PWM2)
        {
            // IOCON_SWDIO_PIO1_3 CT32B1_MAT2 warning : AD4 FUNC=0x3
        #ifdef MCU_IS_LPC1311
            SETBIT(LPC_IOCON->SWDIO_PIO1_3,0);
            SETBIT(LPC_IOCON->SWDIO_PIO1_3,1);
        #endif
        }
    }
    else if(timerSelected==TIMER16_0)
    {
        if( (pwmSelected&PWM0)==PWM0)
        {
            // PIO0_8/MISO0/CT16B0_MAT0/ARM_TRACE_CLK
            SETBIT(LPC_IOCON->PIO0_8,1);

            // ONLY LPC1315 : PIO1_13/DTR/ CT16B0_MAT0/TXD warning, doesn't exist on HVQFN33

        }

        if( (pwmSelected&PWM1)==PWM1)
        {
            // PIO0_9/MOSI0/CT16B0_MAT1/ARM_TRACE_SWV
            SETBIT(LPC_IOCON->PIO0_9,1);

            // ONLY LPC1315 : PIO1_14/DSR/CT16B0_MAT1/RXD
        }

        if( (pwmSelected&PWM2)==PWM2)
        {
            // SWCLK/PIO0_10/ SCK0/CT16B0_MAT2                
            SETBIT(LPC_IOCON->SWCLK_PIO0_10,0);
            SETBIT(LPC_IOCON->SWCLK_PIO0_10,1);

        }
    }
    else
    {
        if( (pwmSelected&PWM0)==PWM0)
        {
        #ifdef MCU_IS_LPC1311
            // PIO1_9/CT16B1_MAT0
            SETBIT(LPC_IOCON->PIO1_9,0);
        #endif

        #ifdef MCU_IS_LPC1315
            // PIO0_21/CT16B1_MAT0/MOSI1
            SETBIT(LPC_IOCON->PIO0_21,0);
        #endif

        }

        if( (pwmSelected&PWM1)==PWM1)
        {
        #ifdef MCU_IS_LPC1311
            // PIO1_10/AD6/ CT16B1_MAT1
            SETBIT(LPC_IOCON->PIO1_10,1);
        #endif

        #ifdef MCU_IS_LPC1315
            // PIO0_22/AD6/CT16B1_MAT1/MISO1
            SETBIT(LPC_IOCON->PIO0_22,1);

            // PIO1_23/CT16B1_MAT1/SSEL1
        #endif
        }
    }

    
}

void setPwmConfig(LPC_TMR_TypeDef * timer, PWMOUTPUT pwmSelected, UInt32 cycle)
{
    if( (pwmSelected&PWM0)==PWM0)
    {
        timer->MR0 = cycle;
        // EM0 is controlled by PWM
        SETBIT(timer->PWMC,0);
        // state of MAT0 output, when start pwm, we set to HIGH
        SETBIT(timer->EMR,0);
        // toggle MAT0 pin output
        timer->EMR |= BITS(4,0x3);        
    }
    
    if( (pwmSelected&PWM1)==PWM1)
    {
        timer->MR1 = cycle;
        SETBIT(timer->PWMC,1);
        SETBIT(timer->EMR,1);
        timer->EMR |= BITS(6,0x3);
    }
    
    if( (pwmSelected&PWM2)==PWM2)
    {
        timer->MR2 = cycle;
        SETBIT(timer->PWMC,2);
        SETBIT(timer->EMR,2);
        timer->EMR |= BITS(8,0x3);
    }
}

void setPwmCycle(LPC_TMR_TypeDef * timer, PWMOUTPUT pwmSelected, UInt32 cycle)
{
    if( (pwmSelected&PWM0)==PWM0)
    {
        timer->MR0 = cycle;
    }
    
    if( (pwmSelected&PWM1)==PWM1)
    {
        timer->MR1 = cycle;
    }
    
    if( (pwmSelected&PWM2)==PWM2)
    {
        timer->MR2 = cycle;
    }
}




//-------------------------- public functions:


void initPwm(Pwm *pwm, PWMTIMER timerSelected,PWMOUTPUT pwmSelected, UInt32 widthInUs, UInt32 widthDivider, UInt32 percentage)
{
    UInt32 widthPwm, cycle;
    
    // power on timer module
    // SYSAHBCLKCTRL bit9 1 = timer0 bit10 1 =timer1 (32 bits)
    if( timerSelected == TIMER32_0)
    {
        pwm->timer = LPC_TMR32B0;
        SETBIT(LPC_SYSCON->SYSAHBCLKCTRL,9);
  
//TODO
//        NVIC_SetPriority(TIMER_32_0_IRQn, 0x04);
//        NVIC_EnableIRQ(TIMER_32_0_IRQn);
    }
    else if (timerSelected == TIMER32_1)
    {
        pwm->timer = LPC_TMR32B1;
        SETBIT(LPC_SYSCON->SYSAHBCLKCTRL,10);
  
//TODO
//        NVIC_SetPriority(TIMER_32_1_IRQn, 0x04);
//        NVIC_EnableIRQ(TIMER_32_1_IRQn);
    }

    // SYSAHBCLKCTRL bit7 1 = timer0 bit8 1 =timer1 (16 bits)
    else if( timerSelected == TIMER16_0)
    {
        pwm->timer = LPC_TMR16B0;
        SETBIT(LPC_SYSCON->SYSAHBCLKCTRL,7);
        
        NVIC_SetPriority(TIMER_16_0_IRQn, 0x04);
        NVIC_EnableIRQ(TIMER_16_0_IRQn);
    }
    else
    {
        pwm->timer = LPC_TMR16B1;
        SETBIT(LPC_SYSCON->SYSAHBCLKCTRL,8);
        
        NVIC_SetPriority(TIMER_16_1_IRQn, 0x04);
        NVIC_EnableIRQ(TIMER_16_1_IRQn);
    }
    
    pwm->enable = false;
    pwm->outputs = pwmSelected;
    
    // select output pwm pin 
    setPwmPin(timerSelected,pwmSelected);
    
    
    // For 16 bits timer, when prescaler set to 0, pwm is between 1.1 kHz and 1 MHz

    widthPwm = GET_TICK_FROM_US(widthInUs);
    
    // Set the width divider
    if (widthDivider!=0)
    {
        pwm->timer->PR = widthDivider -1;
    }
    
    //#ifdef PWM_UNIT_100NS
    //    widthPwm = (KERNEL_CPU_FREQ / 1000) * widthInUs -1;
    //#else
    //    widthPwm = (KERNEL_CPU_FREQ / 10000) * widthInUs -1;
    //#endif
    
    
    // MR3 store the pwm period
    pwm->timer->MR3 = widthPwm;

    // MRx store the pwm duty cycle: time the MATx pin is high
    cycle = (widthPwm * (1000 - percentage)) / 1000;
    
    // reset when MR3 match the timer counter
    SETBIT(pwm->timer->MCR,10);
        
    setPwmConfig(pwm->timer,pwmSelected,cycle);
    
    // enable pwm0 and pwm3:
    // 1- when a match occurs in MR0, then MAT0 goes HIGH
    // 2- and timer get the MR3 value
    // 3- when timer reach 0, then MAT0 goes LOW and reloaded with MR0
    SETBIT(pwm->timer->PWMC,3);
    
}

void enablePwm(Pwm *pwm)
{
    LPC_TMR_TypeDef * timer = pwm->timer;
    
    // enable timer and clear reset
    CLRBIT(timer->TCR,1);
    SETBIT(timer->TCR,0);
    
    pwm->enable = true;
}

void disablePwm(Pwm *pwm)
{
    LPC_TMR_TypeDef * timer = pwm->timer;
    
    if (pwm->enable == true)
    {
        // enable interrupt on match 
        pwm_stopped = 0;
        SETBIT(timer->MCR,9);
        
        while(pwm_stopped!=0);
        
        pwm->enable = false;
    }
}

void setPwmDutyCycle(Pwm *pwm, UInt32 percentage)
{
    LPC_TMR_TypeDef * timer = pwm->timer;
    UInt32 widthPwm;
    UInt32 cycle;
        
    widthPwm = timer->MR3;

    // MRx store the pwm duty cycle: time the MATx pin is high
    cycle = (widthPwm * (1000 - percentage)) / 1000;
    
    setPwmCycle(timer, pwm->outputs,cycle);
}


void setPwmWidth(Pwm *pwm, UInt32 widthInUs)
{
    LPC_TMR_TypeDef * timer = pwm->timer;
    UInt32 widthPwm;
           
    //todo 100us = (KERNEL_CPU_FREQ/100)*10 -1
    //todo 10us  = (KERNEL_CPU_FREQ /100) -1
    //todo 1us   = (KERNEL_CPU_FREQ /1000) -1
    
    widthPwm = GET_TICK_FROM_US(widthInUs);
   
    
    timer->TC = 0;
    
    // MR3 store the pwm period
    timer->MR3 = widthPwm;
}