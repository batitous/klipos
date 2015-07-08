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

static const c_speed_t c_speed[] =
{
 { //Initialize CAN Controller 72MHz-100kbps
  0x00000001UL, //CANCLCLKDIV -> div: 2
  0x00001BD7UL  //CAN_BTR     -> BRP: 24, Quanta: 15, Seg1: 12, Seg2: 2, SJW: 4, Sample 86%
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

//--------------------- private variables

static CANMessage       messageReceive;
static volatile uint8_t tx_busy;
//static CAN_ERROR_t      canError;
static KTask *          CANTask;

void CAN_IRQHandler(void)
{
    uint32_t irq = LPC_CAN->INT;
    uint32_t stat = LPC_CAN->STAT;
    uint32_t msg_no = irq & 0x7FFF;
    
    printf("IRQ %x STAT %x no %d\r\n", irq, stat, msg_no);
    
    if ( (stat & BIT(3)) != 0 )
    {
        CLRBIT(LPC_CAN->STAT, 3);
    }
    
    if ( (stat & BIT(4)) != 0 )
    {
        CLRBIT(LPC_CAN->STAT, 4);
        
        
        printf("MCTRL %x\r\n", LPC_CAN->IF2_MCTRL);
        
//        if (msg_no==0)
//        {
//            return;
//        }
        
        while ( LPC_CAN->IF2_CMDREQ & IFCREQ_BUSY );
        
        LPC_CAN->IF2_CMDMSK = RD|MASK|ARB|CTRL|INTPND|TREQ|DATAA|DATAB;
        LPC_CAN->IF2_CMDREQ = msg_no;    /* Start message transfer */
  
  
//        LPC_CAN->IF2_CMDMSK = RD|MASK|ARB|TREQ|DATAA|DATAB;
//        LPC_CAN->IF2_CMDREQ = IFCREQ_BUSY;
        
        while(LPC_CAN->IF2_CMDREQ & IFCREQ_BUSY );	/* Check new data bit */
        
        messageReceive.mode_id = (LPC_CAN->IF2_ARB2 & 0x1FFF) >> 2;
        messageReceive.dataSize = LPC_CAN->IF2_MCTRL & 0x000F;	// Get Msg Obj Data length
        messageReceive.DA1 = LPC_CAN->IF2_DA1;
        messageReceive.DA2 = LPC_CAN->IF2_DA2;
        messageReceive.DB1 = LPC_CAN->IF2_DB1;
        messageReceive.DB2 = LPC_CAN->IF2_DB2;
        
        postEventToTask(CANTask,messageReceive.mode_id);
        
        
    }
    
    
}

void initCANMessage(void)
{
    LPC_CAN->IF1_CMDMSK = WR|MASK|ARB|CTRL|DATAA|DATAB;

    LPC_CAN->IF1_ARB1 = 0x0000;
    LPC_CAN->IF1_ARB2 = ID_MVAL ; //| ID_MTD;
    
    LPC_CAN->IF1_MCTRL = UMSK|RXIE|EOB|DLC_MAX;
    LPC_CAN->IF1_DA1 = 0x0000;
    LPC_CAN->IF1_DA2 = 0x0000;
    LPC_CAN->IF1_DB1 = 0x0000;
    LPC_CAN->IF1_DB2 = 0x0000;
    
    LPC_CAN->IF1_CMDREQ = 1; //IFCREQ_BUSY;
    while( LPC_CAN->IF1_CMDREQ & IFCREQ_BUSY );
    
}

//--------------------- public functions


void initCAN(CANBaudrate kbaud)
{
    // Enable CAN clock and reset
    SETBIT(LPC_SYSCON->SYSAHBCLKCTRL[1],7);
    
    SETBIT(LPC_SYSCON->PRESETCTRL[1], 7);
    CLRBIT(LPC_SYSCON->PRESETCTRL[1], 7);

    SETBIT(LPC_CAN->CNTL, 0); // INIT Start
    
    LPC_CAN->CLKDIV = c_speed[kbaud].div;
    SETBIT(LPC_CAN->CNTL, 6); //CCE
    LPC_CAN->BT = c_speed[kbaud].btr;
    LPC_CAN->BRPE = 0;
    CLRBIT(LPC_CAN->CNTL, 6); //CCE end
    
//    SETBIT(LPC_CAN->CNTL, 7); // TEST
//    SETBIT(LPC_CAN->TEST, 2); // Mode BASIC
    
    CLRBIT(LPC_CAN->CNTL, 0); // Init End
    
    while ( LPC_CAN->CNTL & CTRL_INIT )
    {
        
    }
    
    printf("CNTL %x STAT %x\r\n", LPC_CAN->CNTL, LPC_CAN->STAT);
    printf("BT %x BRPE %x CLKDIV %x\r\n", LPC_CAN->BT, LPC_CAN->BRPE, LPC_CAN->CLKDIV);
    
    initCANMessage();
    
    NVIC_EnableIRQ(CAN_IRQn); 
    
    SETBIT(LPC_CAN->CNTL, 1); //IE
    SETBIT(LPC_CAN->CNTL, 2); //SIE
    SETBIT(LPC_CAN->CNTL, 3); //EIE
}

CANResult sendMessageOnCAN(CANMessage * message)
{
    // check object number
    if((message->msgobj < 1) || (message->msgobj > 20))
    {
        return CAN_TX_WRONG_MSGOBJ; //wrong message object
    }
    
    //read pending transmission request of object
    while(LPC_CAN->TXREQ1 & (1 << message->msgobj))
    {
    }
    
    if (tx_busy==1)
    {
//        return CAN_TX_BUSY;
    }
        
    tx_busy = 1;
//    LPC_CAND_API->hwCAN_MsgTransmit(pCanHandle, (CAN_MSG_OBJ*)message);
    
    LPC_CAN->IF1_ARB2 = ID_MVAL | ID_DIR | (message->mode_id << 2);
    LPC_CAN->IF1_ARB1 = 0x0000;
    /* Mxtd: 0, Mdir: 1, Mask is 0x7FF */
    LPC_CAN->IF1_MSK2 = MASK_MDIR | (ID_STD_MASK << 2);
    LPC_CAN->IF1_MSK1 = 0x0000;
    LPC_CAN->IF1_MCTRL = UMSK|TXRQ|EOB|(message->dataSize & DLC_MASK);
    LPC_CAN->IF1_DA1 =  message->DA1;
    LPC_CAN->IF1_DA2 = message->DA2;
    LPC_CAN->IF1_DB1 = message->DB1;
    LPC_CAN->IF1_DB2 = message->DB2;
    LPC_CAN->IF1_CMDMSK = WR|MASK|ARB|CTRL|TREQ|DATAA|DATAB;
    LPC_CAN->IF1_CMDREQ = IFCREQ_BUSY;

    return CAN_OK;
}

void assignTaskOnCAN(KTask* t)
{
    CANTask = t;
}

CANMessage * receiveMessageFromCAN()
{
    return &messageReceive;
}
