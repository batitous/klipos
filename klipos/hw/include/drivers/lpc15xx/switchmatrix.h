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
#ifndef LIB_HW_SWITCH_MATRIX_H
#define LIB_HW_SWITCH_MATRIX_H

#ifdef __cplusplus
extern "C" {
#endif

#include "switchmatrix-pins.h"

/** @brief Initialize the GPIO swich matrix hardware
 * 
 */
extern void initSwitchMatrix(void);

/** @brief Assign a moving function to a GPIO pin
 * 
 * @param function      Function 
 * @param pin           GPIO 
 */
extern void assignMovableFunctionToGpio(SwitchMatrixMovableFunction function, GPIO_PIN pin);

/** Enable or disable a fixed function on the GPIO
 * 
 * @param function      Function to enable or disable
 * @param enable        True to enable, else false
 */
extern void enableFixedFunction(SwitchMatrixFixexFunction function, bool enable);


#ifdef __cplusplus
 }
#endif

#endif
