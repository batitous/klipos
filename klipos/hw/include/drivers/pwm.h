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
#ifndef LIB_HW_PWM_H
#define LIB_HW_PWM_H

#ifdef __cplusplus
extern "C" {
#endif

/** Check the code and datasheet to know the i/o pins of pwm output
 * 
 * Warning, if you use the same timer for multiple pwm output, your pwm output share the same frequency output !
 * 
 */

typedef enum _pwm_output_
{
#ifdef MCU_IS_LPC13XX
        PWM0 = 0x01,        /**< PWM output 0 */
        PWM1 = 0x02,        /**< PWM output 1 */
        PWM2 = 0x04         /**< PWM output 2 */
#endif

#ifdef MCU_IS_LPC15XX
       PWM0 = 0xFF
#endif
                
#ifdef MCU_IS_LPC17XX
        PWM1 = 0x01,
        PWM2 = 0x02,
        PWM3 = 0x04,
        PWM4 = 0x08,
        PWM5 = 0x10,
        PWM6 = 0x20
#endif
} PWMOUTPUT;


typedef enum _timertype_
{
    TIMER32_0 = 0,
    TIMER32_1 = 1,
    TIMER16_0 = 2,
    TIMER16_1 = 3
} PWMTIMER;


typedef struct _pwm_device_
{
#if defined(MCU_IS_LPC15XX)

#else
    LPC_TMR_TypeDef     *timer;
#endif
    PWMOUTPUT           outputs;
    bool                enable;
} Pwm;


/** @brief Init PWM driver.
 * 
 * @param pwm                   Output pwm object.
 * @param timerType             Select a timer for the PWM.
 * @param pwmSelected           Select an PWM output (or multiple PWM output).
 * @param widthInUs             PWM period in us.
 * @param widthDivider          Constant to divide your period (to lower PWM frequency)
 * @param percentage            Duty cycle (between 0% and 1000%).
 */
extern void initPwm(Pwm *pwm, PWMTIMER timerType, PWMOUTPUT pwmSelected, uint32_t widthInUs, uint32_t widthDivider, uint32_t percentage);


/** @brief Enable or Disable PWM.
 * 
 * @param pwm           Pwm object.
 */
extern void enablePwm(Pwm *pwm);
extern void disablePwm(Pwm *pwm);


/** @brief Set PWM duty cycle.
 * 
 * @param pwm                   Pwm object.
 * @param percentage            Set duty cycle (between 0% and 1000%).
 */
extern void setPwmDutyCycle(Pwm *pwm, uint32_t percentage);

extern void setPwmRawDutyCycle(Pwm *pwm, uint32_t raw);

extern void setPwmWidth(Pwm *pwm, uint32_t widthInUs);



#ifdef __cplusplus
 }
#endif

#endif