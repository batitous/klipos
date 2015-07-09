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
#ifndef LIB_HW_CAN_H
#define	LIB_HW_CAN_H

#ifdef	__cplusplus
extern "C" {
#endif


typedef enum _can_baudrate_
{
    CAN_BAUDRATE_100    = 0,
    CAN_BAUDRATE_125    = 1,
    CAN_BAUDRATE_250    = 2,
    CAN_BAUDRATE_500    = 3,
    CAN_BAUDRATE_1000   = 4
} CANBaudrate;

typedef struct _can_message_object_
{
    uint32_t    id;
    uint8_t     data[8];
    uint8_t     size;
} CANMessage;


extern void initCAN(CANBaudrate kbaud);
extern void assignTaskOnCAN(KTask* t);

extern void registerReceiverIdCAN(uint32_t id);

extern bool sendMessageOnCAN(CANMessage * message);
extern CANMessage * receiveMessageFromCAN();

#ifdef	__cplusplus
}
#endif

#endif	/* CAN_H */

