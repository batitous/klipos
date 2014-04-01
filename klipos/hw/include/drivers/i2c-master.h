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
#ifndef LIB_HW_I2C_MASTER_H
#define LIB_HW_I2C_MASTER_H

#ifdef __cplusplus
extern "C" {
#endif


typedef enum _i2c_speed
{
    I2C_100_KHZ=0,		/**< I2C speed frequency 100 KHz */
    I2C_400_KHZ=1		/**< I2C speed frequency 400 KHz */
} I2C_SPEED;


#define I2C_OK          0   /**< Last operation on i2c bus is OK. */
#define I2C_ERROR       1   /**< Error on i2c bus. */
#define I2C_ERROR_START 2   /**< Error when send START bit on i2c bus. */
#define I2C_ERROR_SEND  3   /**< Error when send data on i2c bus. */
#define I2C_BUSY        4   /**< i2c bus is busy. */
#define I2C_EMPTY       5   /**< i2c buffer is empty. */
#define I2C_TIMEOUT     6   /**< Operation timeout on i2c bus */


extern const I2cMaster * initI2c0(I2C_SPEED speed);

extern uint32_t sendBufferToI2c0(uint8_t addr, uint8_t *buffer, uint32_t len);

extern uint32_t getBufferFromI2c0(uint8_t addr, uint8_t *buffer, uint32_t len);


#ifdef __cplusplus
}
#endif

#endif
