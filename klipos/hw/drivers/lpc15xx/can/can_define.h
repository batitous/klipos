/* 
 * File:   can_define.h
 * Author: baptiste
 *
 * Created on 7 juillet 2015, 15:45
 */

#ifndef CAN_DEFINE_H
#define	CAN_DEFINE_H

/*------------- CAN Controller (CAN) ----------------------------*/
/** @addtogroup LPC15xx_CAN LPC15xx Controller Area Network(CAN)
  @{
*/
typedef struct
{
  __IO uint32_t CNTL;				/* 0x000 */
  __IO uint32_t STAT;
  __I  uint32_t EC;
  __IO uint32_t BT;
  __I  uint32_t INT;
  __IO uint32_t TEST;
  __IO uint32_t BRPE;
       uint32_t RESERVED0;
  __IO uint32_t IF1_CMDREQ;			/* 0x020 */
  __IO uint32_t IF1_CMDMSK;
  __IO uint32_t IF1_MSK1;
  __IO uint32_t IF1_MSK2;
  __IO uint32_t IF1_ARB1;
  __IO uint32_t IF1_ARB2;
  __IO uint32_t IF1_MCTRL;
  __IO uint32_t IF1_DA1;
  __IO uint32_t IF1_DA2;
  __IO uint32_t IF1_DB1;
  __IO uint32_t IF1_DB2;
       uint32_t RESERVED1[13];
  __IO uint32_t IF2_CMDREQ;			/* 0x080 */
  __IO uint32_t IF2_CMDMSK;
  __IO uint32_t IF2_MSK1;
  __IO uint32_t IF2_MSK2;
  __IO uint32_t IF2_ARB1;
  __IO uint32_t IF2_ARB2;
  __IO uint32_t IF2_MCTRL;
  __IO uint32_t IF2_DA1;
  __IO uint32_t IF2_DA2;
  __IO uint32_t IF2_DB1;
  __IO uint32_t IF2_DB2;
       uint32_t RESERVED2[21];
  __I  uint32_t TXREQ1;				/* 0x100 */
  __I  uint32_t TXREQ2;
       uint32_t RESERVED3[6];
  __I  uint32_t ND1;				/* 0x120 */
  __I  uint32_t ND2;
       uint32_t RESERVED4[6];
  __I  uint32_t IR1;				/* 0x140 */
  __I  uint32_t IR2;
       uint32_t RESERVED5[6];
  __I  uint32_t MSGV1;				/* 0x160 */
  __I  uint32_t MSGV2;
       uint32_t RESERVED6[6];
  __IO uint32_t CLKDIV;				/* 0x180 */
} LPC_CAN_TypeDef;
/*@}*/ /* end of group LPC15xx_CAN */


#define LPC_CAN               ((LPC_CAN_TypeDef *)LPC_C_CAN0_BASE)

#define CAN_STATUS_INTERRUPT      0x8000
#define DLC_MAX				8

/* bit field of IF command mask register */
#define	DATAB	(1 << 0)   /* 1 is transfer data byte 4-7 to message object, 0 is not */
#define	DATAA	(1 << 1)   /* 1 is transfer data byte 0-3 to message object, 0 is not */
#define	TREQ	(1 << 2)   /* 1 is set the TxRqst bit, 0 is not */
#define	INTPND	(1 << 3)
#define	CTRL	(1 << 4)   /* 1 is transfer the CTRL bit to the message object, 0 is not */
#define	ARB	(1 << 5)   /* 1 is transfer the ARB bits to the message object, 0 is not */
#define	MASK	(1 << 6)   /* 1 is transfer the MASK bit to the message object, 0 is not */
#define	WR	(1 << 7)   /* 0 is READ, 1 is WRITE */
#define RD      0x0000

/* bit field of IF mask 2 register */
#define	MASK_MXTD	(1 << 15)     /* 1 extended identifier bit is used in the RX filter unit, 0 is not */
#define	MASK_MDIR	(1 << 14)     /* 1 direction bit is used in the RX filter unit, 0 is not */

/* bit field of IF identifier 2 register */
#define	ID_MVAL		(1 << 15)     /* Message valid bit, 1 is valid in the MO handler, 0 is ignored */
#define	ID_MTD		(1 << 14)     /* 1 extended identifier bit is used in the RX filter unit, 0 is not */
#define	ID_DIR		(1 << 13)     /* 1 direction bit is used in the RX filter unit, 0 is not */

/* bit field of IF message control register */
#define	NEWD		(1 << 15)     /* 1 indicates new data is in the message buffer.  */
#define	MLST		(1 << 14)     /* 1 indicates a message loss. */
#define	INTP		(1 << 13)     /* 1 indicates message object is an interrupt source */
#define UMSK    	(1 << 12)     /* 1 is to use the mask for the receive filter mask. */
#define	TXIE		(1 << 11)     /* 1 is TX interrupt enabled */
#define	RXIE		(1 << 10)     /* 1 is RX interrupt enabled */
#define	ROEN		(1 << 9)      /* 1 is remote frame enabled */
#define TXRQ    	(1 << 8)      /* 1 is TxRqst enabled */
#define	EOB		(1 << 7)      /* End of buffer, always write to 1 */
#define	DLC		0x000F        /* bit mask for DLC */

#define ID_STD_MASK	0x07FF
#define ID_EXT_MASK	0x1FFFFFFF
#define DLC_MASK	0x0F

/* CAN Status register */
#define STAT_LEC		(0x7 << 0)
#define STAT_TXOK		(1 << 3)
#define STAT_RXOK		(1 << 4)
#define STAT_EPASS		(1 << 5)
#define STAT_EWARN		(1 << 6)
#define STAT_BOFF		(1 << 7)

/* CAN CTRL register */
#define CTRL_INIT		(1 << 0)
#define CTRL_IE			(1 << 1)
#define CTRL_SIE		(1 << 2)
#define CTRL_EIE		(1 << 3)
#define CTRL_DAR		(1 << 5)
#define CTRL_CCE		(1 << 6)
#define CTRL_TEST		(1 << 7)

/* CAN TEST register */
#define TEST_BASIC		(1 << 2)
#define TEST_SILENT		(1 << 3)
#define TEST_LBACK		(1 << 4)


typedef struct _CAN_ERROR
{
    uint32_t Pass_Cnt;
    uint32_t WARN_Cnt;
    uint32_t BOff_Cnt;
    uint32_t STUF_Cnt;
    uint32_t FORM_Cnt;
    uint32_t ACK_Cnt;
    uint32_t BIT1_Cnt;
    uint32_t BIT0_Cnt;
    uint32_t CRC_Cnt;
} CAN_ERROR_t;

typedef struct _c_speed
{
    uint32_t div;
    uint32_t btr;
} c_speed_t;



#endif	/* CAN_DEFINE_H */

