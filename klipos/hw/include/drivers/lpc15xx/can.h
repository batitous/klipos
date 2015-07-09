/* 
 * File:   can.h
 * Author: baptiste
 *
 * Created on 7 juillet 2015, 15:35
 */

#ifndef CAN_H
#define	CAN_H

#ifdef	__cplusplus
extern "C" {
#endif

//#define DAR_MODE      //disable auto retransmission
//#define LOOPBACK_MODE	//enable LOOPBACK

typedef enum _can_baudrate_
{
    CAN_BAUDRATE_100 = 0,
    CAN_BAUDRATE_125 = 1,
    CAN_BAUDRATE_250 = 2,
    CAN_BAUDRATE_500 = 3,
    CAN_BAUDRATE_1000 = 4
} CANBaudrate;
    
typedef enum _can_result_
{
    CAN_OK              = 0,
    CAN_TX_BUSY         = 1, // tx on CAN bus is busy 
    CAN_TX_WRONG_MSGOBJ = 2  // wrong msgobj in CANMessage structure
} CANResult;

typedef struct _can_message_object_
{
    uint32_t id;
    uint32_t mask;
        
    union
    {
        uint8_t   data[8];
        struct
        {
            uint32_t DatA;
            uint32_t DatB;
        };

        struct
        {
           uint16_t DA1;
           uint16_t DA2;
           uint16_t DB1;
           uint16_t DB2;
        };
    };
    
    uint8_t size;
    uint8_t msgobj;
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

