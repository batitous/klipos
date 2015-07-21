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

#include "../../../include/libs-klipos.h"
#include "can_define.h"


//--------------------- Baudrate settings

/* http://www.bittiming.can-wiki.info/#NXP
 select Bosch C_CAN / D_CAN

 Can Clock = 72 MHz / Can Div
 Bit Rate = Can Clock / ( (BRP+1) * (TSEG1 + 2 + TSEG2 +1 )

*/

static const c_speed_t c_speed[] =
{
 { //Initialize CAN Controller 72MHz-100kbps
     5UL,
     0x6FC4UL // SegTime=24 Seg1 = 16 Seg2 = 8
//     0x1cc4UL

//  0x00000001UL, //CANCLCLKDIV -> div: 2
//  0x00001BD7UL  //CAN_BTR     -> BRP: 24, Quanta: 15, Seg1: 12, Seg2: 2, SJW: 4, Sample 86%
 },
 { //Initialize CAN Controller 72MHz-125kbps
  0x00000001UL, //CANCLCLKDIV -> div: 2
  0x00001CD1UL  //CAN_BTR     -> BRP: 18, Quanta: 16, Seg1: 13, Seg2: 2, SJW: 4, Sample 87%
 },
 { //Initialize CAN Controller 72MHz-250kbps
  0x00000000UL, //CANCLCLKDIV -> div: 1
  0x00001CD1UL  //CAN_BTR     -> BRP: 18, Quanta: 16, Seg1: 13, Seg2: 2, SJW: 4, Sample 87%
 },
 { //Initialize CAN Controller 72MHz-500kbps
  0x00000000UL, //CANCLCLKDIV -> div: 1
  0x00001CC8UL  //CAN_BTR     -> BRP: 9, Quanta: 16, Seg1: 13, Seg2: 2, SJW: 4, Sample 87%
 },
 { //Initialize CAN Controller 72MHz-1000kbps
  0x00000000UL, //CANCLCLKDIV -> div: 1
  0x000009C5UL, //CAN_BTR     -> BRP: 6, Quanta: 12, Seg1: 10, Seg2: 1, SJW: 4, Sample 91%
 },
};

//--------------------- private defines

#define CAN_MSG_SIZE    8

//--------------------- private variables

static uint32_t                 messageGetIndex;
static volatile uint32_t        messageSetIndex;
static volatile CANMessage      messages[CAN_MSG_SIZE];
static KTask *                  CANTask;


//--------------------- private functions


static void CCAN_TransferMsgObject(uint32_t commandMask,uint32_t msgNum)
{
    msgNum &= 0x3F;
    LPC_CAN->IF1_CMDMSK = commandMask;
    LPC_CAN->IF1_CMDREQ = msgNum;
    
    while (LPC_CAN->IF1_CMDREQ & CCAN_IF_CMDREQ_BUSY ) {}
}

static bool CCAN_GetMsgObject(uint8_t msgNum, CANMessage *pMsgObj)
{
    uint32_t *pData = (uint32_t *) pMsgObj->data;
    
    CCAN_TransferMsgObject(CCAN_IF_CMDMSK_RD | CCAN_IF_CMDMSK_TRANSFER_ALL | CCAN_IF_CMDMSK_R_CLRINTPND,
                           msgNum);

    if (LPC_CAN->IF1_MCTRL & CCAN_IF_MCTRL_NEWD) 
    {
        pMsgObj->id = (LPC_CAN->IF1_ARB1) | (LPC_CAN->IF1_ARB2 << 16);
        pMsgObj->size = LPC_CAN->IF1_MCTRL & CCAN_IF_MCTRL_DLC_MSK;
        *pData++ = (LPC_CAN->IF1_DA2 << 16) | LPC_CAN->IF1_DA1;
        *pData = (LPC_CAN->IF1_DB2 << 16) | LPC_CAN->IF1_DB1;

        if (pMsgObj->id & (0x1 << 30)) 
        {
            pMsgObj->id &= CCAN_MSG_ID_EXT_MASK;
        }
        else 
        {
            pMsgObj->id >>= 18;
            pMsgObj->id &= CCAN_MSG_ID_STD_MASK;
        }
        
        return true;
    }
    
    return false;
}

void CAN_IRQHandler(void)
{
    uint32_t can_int;
    uint32_t can_stat;
        
    while ( (can_int=LPC_CAN->INT) != 0 )
    {
        if (can_int & CCAN_INT_STATUS) 
        {
            can_stat = LPC_CAN->STAT;    
            
            // TODO with error or TXOK, RXOK
            if (can_stat & CCAN_STAT_EPASS)
            {
                printf("Passive error\r\n");
            }
            if (can_stat & CCAN_STAT_EWARN) 
            {
                printf("Warning!!!\r\n");
            }
            if (can_stat & CCAN_STAT_BOFF) 
            {
                printf("CAN bus is off\r\n");
            }
            
            CLRBIT(LPC_CAN->STAT, 3);
            CLRBIT(LPC_CAN->STAT, 4);
        }
        else if ((1 <= can_int) && (can_int <= 0x20)) 
        {
            if (CCAN_GetMsgObject(can_int, (CANMessage *)&messages[messageSetIndex])==true)
            {
                postEventToTask(CANTask,messages[messageSetIndex].id);
                
                messageSetIndex++;
                if (messageSetIndex==CAN_MSG_SIZE)
                {
                    messageSetIndex=0;
                }
            }
        }
    }

}

static uint8_t getFreeMsgObject()
{
    uint8_t i;
    uint32_t msg_valid = CCAN_GetValidMsg();

    for (i = 0; i < CCAN_MSG_MAX_NUM; i++)
    {
        if (!((msg_valid >> i) & 1UL))
        {
            return i + 1;
        }
    }
    
    return 0;	// No free object
}

static void CCAN_SetValidMsg(uint8_t msgNum, bool valid)
{
    uint32_t temp = LPC_CAN->IF1_ARB2;
    
    if (!valid) 
    {
        LPC_CAN->IF1_ARB2 = (temp & (~CCAN_IF_ARB2_MSGVAL));
    }
    else 
    {
        LPC_CAN->IF1_ARB2 = (temp | (CCAN_IF_ARB2_MSGVAL));
    }

    CCAN_TransferMsgObject(CCAN_IF_CMDMSK_WR | CCAN_IF_CMDMSK_ARB, msgNum);
}

static void CCAN_SetMsgObject(CCAN_TRANSFER_DIR_T dir, bool remoteFrame, uint8_t msgNum, const CANMessage *pMsgObj)
{
    uint16_t *pData;
    uint32_t msgCtrl = 0;

    pData = (uint16_t *) (pMsgObj->data);

    msgCtrl |= CCAN_IF_MCTRL_UMSK | CCAN_IF_MCTRL_RMTEN(remoteFrame) | CCAN_IF_MCTRL_EOB |
                       (pMsgObj->size & CCAN_IF_MCTRL_DLC_MSK);
    
    if (dir == CCAN_TX_DIR) 
    {
        msgCtrl |= CCAN_IF_MCTRL_TXIE;
        if (!remoteFrame) 
        {
            msgCtrl |= CCAN_IF_MCTRL_TXRQ;
        }
    }
    else 
    {
        msgCtrl |= CCAN_IF_MCTRL_RXIE;
    }

    LPC_CAN->IF1_MCTRL = msgCtrl;
    LPC_CAN->IF1_DA1 = *pData++;	/* Lower two bytes of message pointer */
    LPC_CAN->IF1_DA2 = *pData++;	/* Upper two bytes of message pointer */
    LPC_CAN->IF1_DB1 = *pData++;	/* Lower two bytes of message pointer */
    LPC_CAN->IF1_DB2 = *pData;	/* Upper two bytes of message pointer */

    /* Configure arbitration */
    if (!(pMsgObj->id & (0x1 << 30))) 
    {					
        /* bit 30 is 0, standard frame */
        /* Mxtd: 0, Mdir: 1, Mask is 0x7FF */
        LPC_CAN->IF1_MSK2 = CCAN_IF_MASK2_MDIR(dir) | (CCAN_MSG_ID_STD_MASK << 2);
        LPC_CAN->IF1_MSK1 = 0x0000;

        /* MsgVal: 1, Mtd: 0, Dir: 1, ID = 0x200 */
        LPC_CAN->IF1_ARB2 = CCAN_IF_ARB2_MSGVAL | CCAN_IF_ARB2_DIR(dir) | (pMsgObj->id << 2);
        LPC_CAN->IF1_ARB1 = 0x0000;
    }
    else 
    {										/* Extended frame */
        /* Mxtd: 1, Mdir: 1, Mask is 0x1FFFFFFF */
        LPC_CAN->IF1_MSK2 = CCAN_IF_MASK2_MXTD | CCAN_IF_MASK2_MDIR(dir) | (CCAN_MSG_ID_EXT_MASK >> 16);
        LPC_CAN->IF1_MSK1 = CCAN_MSG_ID_EXT_MASK & 0x0000FFFF;

        /* MsgVal: 1, Mtd: 1, Dir: 1, ID = 0x200000 */
        LPC_CAN->IF1_ARB2 = CCAN_IF_ARB2_MSGVAL | CCAN_IF_ARB2_XTD | CCAN_IF_ARB2_DIR(dir) | (pMsgObj->id >> 16);
        LPC_CAN->IF1_ARB1 = pMsgObj->id & 0x0000FFFF;
    }

    CCAN_TransferMsgObject(CCAN_IF_CMDMSK_WR | CCAN_IF_CMDMSK_TRANSFER_ALL, msgNum);
}

//--------------------- public functions


void initCAN(CANBaudrate kbaud)
{
    uint32_t i;
    
    messageSetIndex = 0;
    messageGetIndex = 0;
    
     // Enable CAN clock and reset
    SETBIT(LPC_SYSCON->SYSAHBCLKCTRL[1],7);
    
    SETBIT(LPC_SYSCON->PRESETCTRL[1], 7);
    CLRBIT(LPC_SYSCON->PRESETCTRL[1], 7);
    
    for (i = 1; i <= CCAN_MSG_MAX_NUM; i++) 
    {
        CCAN_SetValidMsg(i, false);
    }
    
    // clear rx tx status
    CLRBIT(LPC_CAN->STAT, 3);
    CLRBIT(LPC_CAN->STAT, 4);
    
    // configure clock
    SETBIT(LPC_CAN->CNTL, 0); // INIT Start
    
    LPC_CAN->CLKDIV = c_speed[kbaud].div;
    SETBIT(LPC_CAN->CNTL, 6); //CCE
    LPC_CAN->BT = c_speed[kbaud].btr;
    LPC_CAN->BRPE = 0;
    CLRBIT(LPC_CAN->CNTL, 6); //CCE end    
    CLRBIT(LPC_CAN->CNTL, 0); // Init End
    
    while ( LPC_CAN->CNTL & BIT(0) ) {}
    
    
    // Enable IRQ
    
    SETBIT(LPC_CAN->CNTL, 1); //IE
    SETBIT(LPC_CAN->CNTL, 2); //SIE
    SETBIT(LPC_CAN->CNTL, 3); //EIE
        
    NVIC_EnableIRQ(CAN_IRQn); 
}

void registerReceiverIdCAN(uint32_t id)
{
    CANMessage temp;
    uint8_t msgNum = getFreeMsgObject();
    if (!msgNum) 
    {
            return;
    }

    temp.id = id;

    CCAN_SetMsgObject(CCAN_RX_DIR, false, msgNum, &temp);
}

bool sendMessageOnCAN(CANMessage * message)
{
    bool remoteFrame = false;
    uint8_t msgNum = getFreeMsgObject();
    if (!msgNum) 
    {
        return false;
    }
    
    CCAN_SetMsgObject(CCAN_TX_DIR, remoteFrame, msgNum, message);
    
    while (CCAN_GetTxRQST() >> (msgNum - 1))
    {	
        // blocking , wait for sending completed
    }
    
    if (!remoteFrame)
    {
        CCAN_SetValidMsg(msgNum, false);
    }
    
    return true;
}

void assignTaskOnCAN(KTask* t)
{
    CANTask = t;
}

CANMessage * receiveMessageFromCAN()
{
    CANMessage * temp = (CANMessage *)&messages[messageGetIndex]; 
    messageGetIndex++;
    if (messageGetIndex==CAN_MSG_SIZE)
    {
        messageGetIndex = 0;
    }
    
    return temp;
}
