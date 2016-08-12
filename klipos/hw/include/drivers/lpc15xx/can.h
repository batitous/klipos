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

/** CAN Bus baudrate */
typedef enum _can_baudrate_
{
    CAN_BAUDRATE_100    = 0,
    CAN_BAUDRATE_125    = 1,
    CAN_BAUDRATE_250    = 2,
    CAN_BAUDRATE_500    = 3,
    CAN_BAUDRATE_1000   = 4
} CANBaudrate;

#define CAN_MESSAGE_SIZE        8

#define CAN_STATE_BUS_OFF       0   // CAN Bus OFF
#define CAN_STATE_BUS_WARN      1   // CAN Bus Warning
#define CAN_STATE_BUS_EPASS     2   // CAN Bus Error Passive


/** CAN Message structure */
typedef struct _can_message_object_
{
    uint32_t    id;                     // Identifier
    uint8_t     data[CAN_MESSAGE_SIZE]; // Data
    uint8_t     size;                   // Size of data
} CANMessage;

// Create an extended CAN identifier
#define SET_EXTENDED_ID(id)         (id | (0x1 << 30))


/** Initialize the CAN bus controller
 * 
 * @param kbaud         CAN's Baudrate
 */
extern void initCAN(CANBaudrate kbaud);


/** Assign a task when a new CAN trame is received
 * 
 * @param t     A task
 */
extern void assignTaskOnCAN(KTask* t);


/** Register a CAN identifer into the receiver's controller
 * 
 * @param id    CAN identifier
 */
extern void registerReceiverIdCAN(uint32_t id);


/** Send a message on the CAN bus
 * 
 * @param message       Message to send
 * @return              True if success
 */
extern bool sendMessageOnCAN(CANMessage * message);


/** Receive a message from the CAN bus
 * 
 * @return Pointer to a CAN message
 */
extern CANMessage * receiveMessageFromCAN();

/** Get state of CAN Bus
 * 
 * @return 
 */
extern uint32_t    getStateCANBus();

#ifdef	__cplusplus
}
#endif

#endif	/* CAN_H */

