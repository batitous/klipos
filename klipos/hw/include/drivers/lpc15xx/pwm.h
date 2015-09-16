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
#ifndef LIB_HW_PWM_H
#define LIB_HW_PWM_H

#ifdef	__cplusplus
extern "C" {
#endif

/** PWM hardware block */    
typedef enum _pwm_sct_
{
    PWM_SCT0  = 0,
    PWM_SCT1  = 1,
    PWM_SCT2  = 2,
    PWM_SCT3  = 3 
} PWM_SCT;


/** PWM output of a PWM hardware block */
typedef enum _pwm_output_
{
       PWM0 = 0x00,
       PWM1 = 0x01,
       PWM2 = 0x02,
       PWM3 = 0x03,
       PWM4 = 0x04,
       PWM5 = 0x05,
       PWM6 = 0x06
} PWM_OUTPUT;


/** PWM object */
typedef struct _pwm_device_
{
    LPC_SCT_T *         sct;
    uint32_t            evt;
    uint32_t            freq;
} Pwm;


/** @brief Compute the prescaler needed from a clock in KHz.
 * 
 * @param clockInKHz         Clock you want to feed to the pwm hardware in KHz
 * @return The correct prescaler, else 0 if failed.
 */
extern uint32_t computePwmPrescalerFromClock(uint32_t clockInKHz);


/** Initialize a PWM on the specified PWM hardware block
 * 
 * @param pwm           Pwm outout object
 * @param sctPwm        PWM hardware block selected
 * @param prescaler     Prescaler clock
 */
extern void initPwm(Pwm * pwm, PWM_SCT sctPwm, uint32_t prescaler);
extern void clonePwm(Pwm *from, Pwm *to);


/** Initialize a PWM output 
 * 
 * @param pwm           a Pwm object initialized
 * @param pwmSelected   PWM output
 * @param widthInUs     Width of PWM in microseconds
 * @param percentage    Duty cycle in percentage between 0 and 1000
 */
extern void setPwmOutput(Pwm *pwm, PWM_OUTPUT pwmSelected, uint32_t widthInUs, uint32_t percentage);


/** @brief Enable or Disable PWM.
 * 
 * @param pwm           Pwm object.
 */
extern void enablePwm(Pwm *pwm);
extern void disablePwm(Pwm *pwm);

/** Set the PWM duty cycle, PWM needs to be disable !
 * 
 * @param pwm           PWM object
 * @param percentage    Duty cycle in percentage between 0 and 1000
 */
extern void setPwmDutyCycle(Pwm *pwm, uint32_t percentage);


/** Set the PWM Period in microseconds, PWM needs to be disable !
 * 
 * @param pwm           PWM object
 * @param widthInUs     Period in microseconds
 */
extern void setPwmWidth(Pwm *pwm, uint32_t widthInUs);


#ifdef	__cplusplus
}
#endif

#endif	/* PWM_H */

