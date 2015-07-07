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

#define MAX_CAN_PARAM_SIZE          512

static uint32_t         gCANapiMem[MAX_CAN_PARAM_SIZE];
static CAN_HANDLE_T     pCanHandle;
static CAN_CFG          gCANConfig;
static CANMessage       messageReceive;
static volatile uint8_t tx_busy;
static CAN_ERROR_t      canError;
static KTask *          CANTask;

static void callbackRxCAN(uint8_t msg_obj_num);
static void callbackTxCAN(uint8_t msg_obj_num);
static void callbackErrorCAN(uint32_t error_info);

CAN_CALLBACKS callbacks = {
	callbackRxCAN,
	callbackTxCAN,
	callbackErrorCAN
};

static void callbackRxCAN(uint8_t msgNumber)
{
    // Determine which CAN message has been received
    messageReceive.msgobj = msgNumber;

    sendByteToUart1('r');
    
    // Now load up the rec_obj structure with the CAN message
    LPC_CAND_API->hwCAN_MsgReceive(pCanHandle, (CAN_MSG_OBJ*)&messageReceive);
        
    postEventToTask(CANTask,messageReceive.mode_id);
}

static void callbackTxCAN(uint8_t msg_obj)
{
    sendByteToUart1('t');
    tx_busy = 0;
}

static void callbackErrorCAN(uint32_t error_info)
{
    sendByteToUart1('e');
    
    if(error_info & CAN_ERROR_PASS) //passive error
    {
        canError.Pass_Cnt++;
    }
    if(error_info & CAN_ERROR_WARN) //warning error
    {
        canError.WARN_Cnt++;
    }
    if(error_info & CAN_ERROR_BOFF) //busoff error
    {
        canError.BOff_Cnt++;
    }
    if(error_info & CAN_ERROR_STUF) //stuf error
    {
        canError.STUF_Cnt++;
    }
    if(error_info & CAN_ERROR_FORM) //form error
    {
        canError.FORM_Cnt++;
    }
    if(error_info & CAN_ERROR_ACK) //ack error
    {
        canError.ACK_Cnt++;
    }
    if(error_info & CAN_ERROR_BIT1) //bit1 error
    {
        canError.BIT1_Cnt++;
    }
    if(error_info & CAN_ERROR_BIT0) //bit0 error
    {
        canError.BIT0_Cnt++;
    }
    if(error_info & CAN_ERROR_CRC) //crc error
    {
        canError.CRC_Cnt++;
    }
}

void CAN_IRQHandler(void)
{
    sendByteToUart1('+');
    
    LPC_CAND_API->hwCAN_Isr(pCanHandle);
}

static void setSpeedCAN(CANBaudrate selection)
{
    gCANConfig.clkdiv = c_speed[selection].div;
    gCANConfig.btr    = c_speed[selection].btr;
}

//--------------------- public functions


void initCAN(CANBaudrate kbaud)
{
    uint32_t maxParamSize;
    uint32_t status;
    CAN_API_INIT_PARAM_T myCANConfig = {0, LPC_C_CAN0_BASE, &gCANConfig, &callbacks, 0, 0};
    
    // Enable CAN clock and reset
    SETBIT(LPC_SYSCON->SYSAHBCLKCTRL[1],7);
    
    SETBIT(LPC_SYSCON->PRESETCTRL[1], 7);
    CLRBIT(LPC_SYSCON->PRESETCTRL[1], 7);

/*
#ifdef LQFP48
    //CAN signal muxing LQFP48
    Chip_IOCON_PinMuxSet(LPC_IOCON, 0, 18, (IOCON_MODE_INACT | IOCON_DIGMODE_EN));
    Chip_IOCON_PinMuxSet(LPC_IOCON, 0, 13, (IOCON_MODE_INACT | IOCON_DIGMODE_EN));
    Chip_SWM_MovablePortPinAssign(SWM_CAN_TD1_O , 0, 18);
    Chip_SWM_MovablePortPinAssign(SWM_CAN_RD1_I,  0, 13);

#endif

#ifdef LQFP64
    // Assign the pins rx 0[11] and tx 0[31] @ LQFP64 
    Chip_IOCON_PinMuxSet(LPC_IOCON, 0, 11, (IOCON_MODE_INACT | IOCON_DIGMODE_EN));
    Chip_IOCON_PinMuxSet(LPC_IOCON, 0, 31, (IOCON_MODE_INACT | IOCON_DIGMODE_EN));
    Chip_SWM_MovablePinAssign(SWM_CAN_RD1_I, 11);	// Rx P0.11 
    Chip_SWM_MovablePinAssign(SWM_CAN_TD1_O, 31);	// Tx P0.31 
#endif*/

    myCANConfig.mem_base = (uint32_t) &gCANapiMem[0];
    gCANConfig.clkdiv = 0; // Target divisor = 1, clkdiv = (target-1) i.e 0

    setSpeedCAN(kbaud);
    gCANConfig.isr_ena = 1;

    // Validate that we reserved enough memory 
    maxParamSize = LPC_CAND_API->hwCAN_GetMemSize(&myCANConfig);
    if (maxParamSize > MAX_CAN_PARAM_SIZE / 4)
    { 
        while ( 1 ) {}
    }

    // Initialize the ROM with specific configuration
    status = LPC_CAND_API->hwCAN_Init(&pCanHandle, &myCANConfig);
    if (status != CAN_ERROR_NONE)
    { 
        while (1) { __WFI();} 
    }

    //change CAN DAR / LOOPBACK if necessary
    LPC_CAN->CNTL &= ~CTRL_CCE;
    
#ifdef DAR_MODE
    LPC_CAN->CNTL |= (CTRL_DAR); //disable retransmission
#endif

//#ifdef LOOPBACK_MODE
    LPC_CAN->CNTL |= (CTRL_TEST);  //enable test
    LPC_CAN->TEST |= (TEST_LBACK); //enable loopback
//#endif

    LPC_CAN->CNTL &= ~CTRL_INIT; //normal operation

    //if (gCANConfig.isr_ena == 1)
    { 
        NVIC_EnableIRQ(CAN_IRQn); 
    }


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
        return CAN_TX_BUSY;
    }
        
    tx_busy = 1;
    LPC_CAND_API->hwCAN_MsgTransmit(pCanHandle, (CAN_MSG_OBJ*)message);
    
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
