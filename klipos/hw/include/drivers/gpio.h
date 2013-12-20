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
#ifndef LIB_HW_GPIO_H
#define LIB_HW_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "gpio-pins.h"
    
/** @brief GPIO Port */
typedef enum _GPIO_PORT_
{
        GPIO_PORT0=0x00000,     /**< gpio port 0 */
        GPIO_PORT1=0x10000,     /**< gpio port 1 */
        GPIO_PORT2=0x20000,     /**< gpio port 2 */
        GPIO_PORT3=0x40000,     /**< gpio port 3 */
#ifdef MCU_IS_LPC17XX
        GPIO_PORT4=0x80000      /**< gpio port 4 */
#endif
} GPIO_PORT;

/** @brief GPIO Edge sense */
typedef enum _GPIO_EDGE_
{
    GPIO_NO_EDGE        = 0x000000,
    GPIO_FALLING_EDGE   = 0x100000,     /**< fall */
    GPIO_RISING_EDGE    = 0x200000,     /**< rise */
#ifdef MCU_IS_LPC13XX
    GPIO_BOTH_EDGE      = 0x400000      /**< fall and rise */
#endif
} GPIO_EDGE;

/** @brief Mask on GPIO Pin and Port */
#define GPIO_MASK       0x0FFFFF

/** @brief Mask on GPIO Edge */
#define GPIO_EDGE_MASK  0xF00000


/** @brief GPIO direction */
typedef enum _GPIO_DIR_
{
    GPIO_IN  = 0,        /**< Digital pin is an Input */
    GPIO_OUT = 1         /**< Digital pin is an Output */
} GPIO_DIR ;


/** @brief Initialize the GPIO MCU hardware and GPIO IRQ
 */
extern void initGpio(void);

/** @brief Set GPIO direction
 * 
 * @param pin   GPIO to set
 * @param dir   Direction of the pin
 */
extern void setGpioDirection(GPIO_PIN pin, GPIO_DIR dir);

/** @brief Set value of GPIO (0 or 1)
 *
 * @param pin   GPIO to set
 * @param bit   value
 */
extern void setGpioValue(GPIO_PIN pin, UInt32 bit);

/** @brief Get value of a GPIO
 *
 * @param pin   GPIO to get
 * @return Value of the pin (0 or 1)
 */
extern UInt32 getGpioValue(GPIO_PIN pin);
 
#ifdef MCU_IS_LPC1315
/** @brief Toggle a GPIO pin
 *
 * @param pin   The pin to toggle
 */
extern void toggleGpio(GPIO_PIN pin);
#endif

#ifdef __cplusplus
 }
#endif

#endif
