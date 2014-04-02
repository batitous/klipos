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
#ifndef LIB_HW_UART_H
#define LIB_HW_UART_H

#ifdef __cplusplus
extern "C" {
#endif

typedef bool (*ReadByteCall)(uint8_t *byte);
typedef uint32_t (*ReadCall)(uint8_t *buffer, uint32_t size);
typedef void (*WriteByteCall)(uint8_t byte);
typedef void (*WriteCall)(uint8_t *buffer, uint32_t size);
typedef uint32_t (*IsByteAvailableCall)(void);

typedef struct _uart_device_
{
    ReadByteCall readByte;      /**< read one byte of data */
    ReadCall     read;          /**< read a buffer from uart */
    WriteByteCall writeByte;    /**< write a byte on uart */
    WriteCall    write;         /**< write a buffer on uart */
    IsByteAvailableCall isAvailable;
} Uart;
    
    

extern const Uart * initUart0(void);


extern void sendByteToUart0(uint8_t byte);
extern void sendBufferToUart0(uint8_t * Buffer,uint32_t Count);

/** @brief Read a buffer of the specified lenght from the uart.
 *
 * If uart is empty:
 *  --> return 0 
 * 
 * If uart have some data available but not the requested lenght
 *  --> return the number of byte currently stored in the uart
 *  --> BUT the data are not written into the buffer !
 * 
 * Else, write into the buffer the requested lenght's byte and return the lenght.
 * 
 * @param buffer        buffer where store the byte read from the uart
 * @param len           number of bytes you want from the uart
 * @return 0 if no bytes available, else number of bytes available in the stream
 */
extern uint32_t getBufferFromUart0(uint8_t * buffer, uint32_t len);
extern bool getByteFromUart0(uint8_t *byte);

#ifdef FIRMWARE_USE_KERNEL_FULL
        extern void waitDataFromUart0(void);
#endif

#ifdef FIRMWARE_USE_KERNEL_SIMPLE
        extern void setTaskOnUart0(KTask* t);
#endif
        
extern uint32_t getByteAvailableOnUart0(void);

extern void powerOnUart0(void);
extern void powerOffUart0(void);



#ifdef __cplusplus
}
#endif

#endif
