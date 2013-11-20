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

typedef bool (*ReadByteCall)(UInt8 *byte);
typedef UInt32 (*ReadCall)(UInt8 *buffer, UInt32 size);
typedef void (*WriteByteCall)(UInt8 byte);
typedef void (*WriteCall)(UInt8 *buffer, UInt32 size);
typedef void (*WaitCall)(void);

typedef struct _uart_device_
{
    WaitCall     wait;
    ReadByteCall readByte;
    ReadCall     read;
    WriteByteCall writeByte;
    WriteCall    write;
} Uart;
    
    

extern const Uart * initUart0(void);


extern void sendByteToUart0(UInt8 byte);
extern void sendBufferToUart0(UInt8 * Buffer,UInt32 Count);

extern UInt32 getBufferFromUart0(UInt8 * buffer, UInt32 len);
extern bool getByteFromUart0(UInt8 *byte);

extern void waitDataFromUart0(void);

extern void powerOnUart0(void);
extern void powerOffUart0(void);



#ifdef __cplusplus
}
#endif

#endif
