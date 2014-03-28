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
#ifndef LIB_HW_GPIO_IRQ_H
#define	LIB_HW_GPIO_IRQ_H

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef FIRMWARE_USE_KERNEL_FULL
/** @brief Enable an Kernel event on a GPIO pin
 *
 * @param pin           Pin
 * @param edge          Falling or Rising edge (only lpc13xx can have both on the same event!)
 * @param callback      event callback
 * @return
 */
        extern void enableEventOnGpio(GPIO_PIN pin, GPIO_EDGE edge, KEventManager *manager, KEventCallback callback);
#endif

#ifdef FIRMWARE_USE_KERNEL_SIMPLE
/** @brief Enable a GPIO IRQ on the specified task
 * 
 * @param task          Task associated with the IRQ pin
 * @param pin           The pin
 * @param edge          Falling or Rising edge (only lpc13xx can have both on the same event!)
 */
        extern void enableGpioIrqOnTask(KTask* task, GPIO_PIN pin, GPIO_EDGE edge);
#endif
        
/** @brief IRQ callback type */
typedef void (*GpioIrqCallback)(UInt32 gpioEvent, UInt32 gpioEdge);


/** @brief Set the GPIO IRQ callback
 * 
 * @param callback      Function to call when a GPIO IRQ comes.
 */
extern void setGpioIrqCallback(GpioIrqCallback callback);


// enable irq "by the hand"
// Use in 2 cases:
// - you have previously disable irq
// - you want manage your own irq without event, you have to set your own gpio irq callback !
extern void enableGpioIrq(GPIO_PIN pin, GPIO_EDGE edge);


// disable only the irq, the event object is not deactivated !

#ifdef MCU_IS_LPC13XX
extern void disableGpioIrq(GPIO_PIN pin);
#endif

#ifdef MCU_IS_LPC17XX
extern void disableGpioIrq(GPIO_PIN pin, GPIO_EDGE edge);
#endif


#ifdef	__cplusplus
}
#endif

#endif	/* GPIO_IRQ_H */

