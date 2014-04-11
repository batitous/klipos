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
        GPIO_PORT3=0x30000,     /**< gpio port 3 */
#ifdef MCU_IS_LPC17XX
        GPIO_PORT4=0x40000      /**< gpio port 4 */
#endif
} GPIO_PORT;

#define GET_GPIO_PORT_NUMBER(pin)  (((pin) & 0xFFFF0000)>>16)


/** @brief GPIO IRQ Type */
typedef enum _GPIO_IRQ_TYPE_
{
    GPIO_NO_EDGE        = 0x0000000,
    GPIO_FALLING_EDGE   = 0x0100000,     /**< fall */
    GPIO_RISING_EDGE    = 0x0200000,     /**< rise */
#ifdef MCU_IS_LPC13XX
    GPIO_BOTH_EDGE      = 0x0400000      /**< fall and rise */
#endif
            
//#ifdef MCU_IS_LPC1315
//     ,GPIO_LOW_LEVEL     = 0x0800000,   /**< low */
//     GPIO_HIGH_LEVEL     = 0x1000000   /**< high */
//#endif

} GPIO_IRQ_TYPE;

/** @brief Mask on GPIO Pin and Port */
#define GPIO_MASK       0x0FFFFF

/** @brief Mask on GPIO IRQ Type */
#define GPIO_TYPE_IRQ_MASK  0x1F00000


/** @brief GPIO direction */
typedef enum _GPIO_DIR_
{
    GPIO_IN  = 0,        /**< Digital pin is an Input */
    GPIO_OUT = 1         /**< Digital pin is an Output */
} GPIO_DIR ;

/** @brief GPIO mode */
typedef enum _GPIO_MODE_
{
    GPIO_MODE_INACTIVE  = 0,    /**< No pull up and no pull-down resistor */
    GPIO_MODE_PULL_DOWN = 0x1,  /**< Pull down resistor activated */
    GPIO_MODE_PULL_UP   = 0x2,  /**< Pull up resistor activated */
    GPIO_MODE_DEFAULT   = 0x2,  /**< Default, pull-up activated */
    GPIO_MODE_REPEATER  = 0x3   /**< Repeater mode */
} GPIO_MODE;



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
extern void setGpioValue(GPIO_PIN pin, uint32_t bit);

/** @brief Get value of a GPIO
 *
 * @param pin   GPIO to get
 * @return Value of the pin (0 or 1)
 */
extern uint32_t getGpioValue(GPIO_PIN pin);
 
#ifdef MCU_IS_LPC1315
/** @brief Toggle a GPIO pin
 *
 * @param pin   The pin to toggle
 */
extern void toggleGpio(GPIO_PIN pin);

/** @brief Set option on GPIO pin
 * 
 * @param pin           Pin to set
 * @param mode          Set mode (pullup, pulldown) to pin
 * @param hysteresis    Enable or disable the hysteresis
 * @param inputInverted Inverse the input
 */
extern void setGpioOption(GPIO_PIN pin, GPIO_MODE mode, bool hysteresis, bool inputInverted);
#endif

#ifdef __cplusplus
 }
#endif

#endif
