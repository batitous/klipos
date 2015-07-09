/* 
 * File:   can_define.h
 * Author: baptiste
 *
 * Created on 7 juillet 2015, 15:45
 */

#ifndef CAN_DEFINE_H
#define	CAN_DEFINE_H

#define CCAN_MSG_MAX_NUM                              32
#define CCAN_IF_CMDREQ_BUSY          0x8000		/* 1 is writing is progress, cleared when RD/WR done */
#define CCAN_INT_STATUS              0x8000             /*!< Status interrupt*/

/* bit field of IF command mask register */
#define CCAN_IF_CMDMSK_DATAB        (1 << 0)		/** 1 is transfer data byte 4-7 to message object, 0 is not */
#define CCAN_IF_CMDMSK_DATAA        (1 << 1)		/** 1 is transfer data byte 0-3 to message object, 0 is not */
#define CCAN_IF_CMDMSK_W_TXRQST     (1 << 2)		/** Request a transmission. Set the TXRQST bit IF1/2_MCTRL. */
#define CCAN_IF_CMDMSK_R_NEWDAT     (1 << 2)		/** Clear NEWDAT bit in the message object */
#define CCAN_IF_CMDMSK_R_CLRINTPND  (1 << 3)		/** Clear INTPND bit in the message object. */
#define CCAN_IF_CMDMSK_CTRL         (1 << 4)		/** 1 is transfer the CTRL bit to the message object, 0 is not */
#define CCAN_IF_CMDMSK_ARB          (1 << 5)		/** 1 is transfer the ARB bits to the message object, 0 is not */
#define CCAN_IF_CMDMSK_MASK         (1 << 6)		/** 1 is transfer the MASK bit to the message object, 0 is not */
#define CCAN_IF_CMDMSK_WR           (1 << 7)		/*  Tranfer direction: Write */
#define CCAN_IF_CMDMSK_RD           (0)				/*  Tranfer direction: Read */
#define CCAN_IF_CMDMSK_TRANSFER_ALL (CCAN_IF_CMDMSK_CTRL | CCAN_IF_CMDMSK_MASK | CCAN_IF_CMDMSK_ARB | \
									 CCAN_IF_CMDMSK_DATAB | CCAN_IF_CMDMSK_DATAA)

/* bit field of IF mask 2 register */
#define CCAN_IF_MASK2_MXTD          (1 << 15)				/* 1 is extended identifier bit is used in the RX filter unit, 0 is not */
#define CCAN_IF_MASK2_MDIR(n)       (((n) & 0x01) <<  14)	/* 1 is direction bit is used in the RX filter unit, 0 is not */

/* bit field of IF arbitration 2 register */
#define CCAN_IF_ARB2_DIR(n)         (((n) & 0x01) << 13)	/* 1: Dir = transmit, 0: Dir = receive */
#define CCAN_IF_ARB2_XTD            (1 << 14)		/* Extended identifier bit is used*/
#define CCAN_IF_ARB2_MSGVAL         (1 << 15)		/* Message valid bit, 1 is valid in the MO handler, 0 is ignored */

/* bit field of IF message control register */
#define CCAN_IF_MCTRL_DLC_MSK        0x000F			/* bit mask for DLC */
#define CCAN_IF_MCTRL_EOB           (1 << 7)		/* End of buffer, always write to 1 */
#define CCAN_IF_MCTRL_TXRQ          (1 << 8)		/* 1 is TxRqst enabled */
#define CCAN_IF_MCTRL_RMTEN(n)      (((n) & 1UL) << 9)	/* 1 is remote frame enabled */
#define CCAN_IF_MCTRL_RXIE          (1 << 10)		/* 1 is RX interrupt enabled */
#define CCAN_IF_MCTRL_TXIE          (1 << 11)		/* 1 is TX interrupt enabled */
#define CCAN_IF_MCTRL_UMSK          (1 << 12)		/* 1 is to use the mask for the receive filter mask. */
#define CCAN_IF_MCTRL_INTP          (1 << 13)		/* 1 indicates message object is an interrupt source */
#define CCAN_IF_MCTRL_MLST          (1 << 14)		/* 1 indicates a message loss. */
#define CCAN_IF_MCTRL_NEWD          (1 << 15)		/* 1 indicates new data is in the message buffer.  */

#define CCAN_MSG_ID_STD_MASK        0x07FF
#define CCAN_MSG_ID_EXT_MASK        0x1FFFFFFF

#define CCAN_STAT_EPASS     (1 << 5)	/* The CAN controller is in the error passive state*/
#define CCAN_STAT_EWARN     (1 << 6)	/*At least one of the error counters in the EC has reached the error warning limit of 96.*/
#define CCAN_STAT_BOFF      (1 << 7)	/*The CAN controller is in busoff state.*/


typedef struct _c_speed
{
    uint32_t div;
    uint32_t btr;
} c_speed_t;

typedef enum {
	CCAN_RX_DIR,
	CCAN_TX_DIR,
} CCAN_TRANSFER_DIR_T;

#define CCAN_GetValidMsg()      (LPC_CAN->MSGV1 | (LPC_CAN->MSGV2 << 16))
#define CCAN_GetTxRQST()        (LPC_CAN->TXREQ1 | (LPC_CAN->TXREQ2 << 16))


#endif	/* CAN_DEFINE_H */

