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
#ifndef LIB_HW_SLEEP_H
#define LIB_HW_SLEEP_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum _sleep_mode
{
    SLEEP_DEFAULT       = 0x01,         /**< Default sleep, wakeup from any IRQ : nothing to do */
    SLEEP_DEEP          = 0x02,         /**< Deep sleep, you have to set your own wakeup source */
    SLEEP_DEEP_POWERDOWN= 0x04          /**< Deep power down sleep, wakeup very specific, don't use this... */
}SLEEPMODE;


/** @brief Put hardware into sleep
 * 
 * @param mode          Selected sleep (SLEEP_DEEP)
 */
extern void setMcuToSleep(SLEEPMODE mode);

/** @brief Initialize the wakeup source for the hardware 
 * 
 * DONT CALL IT DIRECTLY
 * 
 */
extern void initWakeUp(void);


// Macro for the idle kernel thread 
// Uses a macro for reduce footprint of kernel (avoid sleep.o linking)
#ifdef MCU_IS_LPC17XX
#       define setMcuToDefaultSleep()  LPC_SC->PCON = 0; SCB->SCR = 0; __WFI();
#endif
       
#ifdef MCU_IS_LPC13XX
#       define setMcuToDefaultSleep()    CLRBIT(LPC_PMU->PCON,1); SETBIT(LPC_PMU->PCON,11); CLRBIT(SCB->SCR,2); __WFI();
#endif

#ifdef MCU_IS_LPC15XX
#       define setMcuToDefaultSleep()    /*SETBIT(LPC_PMU->PCON,8); SETBIT(LPC_PMU->PCON,11); __WFI();*/
#endif


#ifdef __cplusplus
 }
#endif

#endif