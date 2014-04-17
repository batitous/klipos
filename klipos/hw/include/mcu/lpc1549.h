/****************************************************************************
 *   LPC13xx.h - 2011-04-28
 *
 *   Based on original by NXP with modifications by Code Red Technologies
 *
 *   Project: NXP LPC13xx software example
 *
 *   Description:
 *     CMSIS Cortex-M3 Core Peripheral Access Layer Header File for
 *     NXP LPC13xx Device Series
 *
 ****************************************************************************
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * products. This software is supplied "AS IS" without any warranties.
 * NXP Semiconductors assumes no responsibility or liability for the
 * use of the software, conveys no license or title under any patent,
 * copyright, or mask work right to the product. NXP Semiconductors
 * reserves the right to make changes in the software without
 * notification. NXP Semiconductors also make no representation or
 * warranty that such application will be suitable for the specified
 * use without further testing or modification.
****************************************************************************/

#ifndef __LPC1549_H__
#define __LPC1549_H__

#ifdef __cplusplus
extern "C" {
#endif

    
/*
 * ==========================================================================
 * ---------- Interrupt Number Definition -----------------------------------
 * ==========================================================================
 */

typedef enum IRQn {
	Reset_IRQn                    = -15,	/*!< Reset Vector, invoked on Power up and warm reset */
	NonMaskableInt_IRQn           = -14,	/*!< Non maskable Interrupt, cannot be stopped or preempted */
	HardFault_IRQn                = -13,	/*!< Hard Fault, all classes of Fault               */
	MemoryManagement_IRQn         = -12,	/*!< Memory Management, MPU mismatch, including Access Violation and No Match */
	BusFault_IRQn                 = -11,	/*!< Bus Fault, Pre-Fetch-, Memory Access Fault, other address/memory related Fault */
	UsageFault_IRQn               = -10,	/*!< Usage Fault, i.e. Undef Instruction, Illegal State Transition */
	SVCall_IRQn                   =  -5,	/*!< System Service Call via SVC instruction         */
	DebugMonitor_IRQn             =  -4,	/*!< Debug Monitor                                   */
	PendSV_IRQn                   =  -2,	/*!< Pendable request for system service             */
	SysTick_IRQn                  =  -1,	/*!< System Tick Timer                               */

	WDT_IRQn                      = 0,		/*!< Watchdog timer Interrupt                         */
	WWDT_IRQn                     = WDT_IRQn,	/*!< Watchdog timer Interrupt alias for WDT_IRQn    */
	BOD_IRQn                      = 1,		/*!< Brown Out Detect(BOD) Interrupt                  */
	FMC_IRQn                      = 2,		/*!< FLASH Interrupt                                  */
	FLASHEEPROM_IRQn              = 3,		/*!< EEPROM controller interrupt                      */
	DMA_IRQn                      = 4,		/*!< DMA Interrupt                                    */
	GINT0_IRQn                    = 5,		/*!< GPIO group 0 Interrupt                           */
	GINT1_IRQn                    = 6,		/*!< GPIO group 1 Interrupt                           */
	PIN_INT0_IRQn                 = 7,		/*!< Pin Interrupt 0                                  */
	PIN_INT1_IRQn                 = 8,		/*!< Pin Interrupt 1                                  */
	PIN_INT2_IRQn                 = 9,		/*!< Pin Interrupt 2                                  */
	PIN_INT3_IRQn                 = 10,		/*!< Pin Interrupt 3                                  */
	PIN_INT4_IRQn                 = 11,		/*!< Pin Interrupt 4                                  */
	PIN_INT5_IRQn                 = 12,		/*!< Pin Interrupt 5                                  */
	PIN_INT6_IRQn                 = 13,		/*!< Pin Interrupt 6                                  */
	PIN_INT7_IRQn                 = 14,		/*!< Pin Interrupt 7                                  */
	RITIMER_IRQn                  = 15,		/*!< RITIMER interrupt                                */
	SCT0_IRQn                     = 16,		/*!< SCT0 interrupt                                   */
	SCT_IRQn                      = SCT0_IRQn,	/*!< Optional alias for SCT0_IRQn                  */
	SCT1_IRQn                     = 17,		/*!< SCT1 interrupt                                   */
	SCT2_IRQn                     = 18,		/*!< SCT2 interrupt                                   */
	SCT3_IRQn                     = 19,		/*!< SCT3 interrupt                                   */
	MRT_IRQn                      = 20,		/*!< MRT interrupt                                    */
	UART0_IRQn                    = 21,		/*!< UART0 Interrupt                                  */
	UART1_IRQn                    = 22,		/*!< UART1 Interrupt                                  */
	UART2_IRQn                    = 23,		/*!< UART2 Interrupt                                  */
	I2C0_IRQn                     = 24,		/*!< I2C0 Interrupt                                   */
	I2C_IRQn                      = I2C0_IRQn,	/*!< Optional alias for I2C0_IRQn                  */
	SPI0_IRQn                     = 25,		/*!< SPI0 Interrupt                                   */
	SPI1_IRQn                     = 26,		/*!< SPI1 Interrupt                                   */
	CAN_IRQn                      = 27,		/*!< CAN Interrupt                                    */
	USB0_IRQn                     = 28,		/*!< USB IRQ interrupt                                */
	USB_IRQn                      = USB0_IRQn,	/*!< Optional alias for USB0_IRQn                  */
	USB0_FIQ_IRQn                 = 29,		/*!< USB FIQ interrupt                                */
	USB_FIQ_IRQn                  = USB0_FIQ_IRQn,	/*!< Optional alias for USB0_FIQ_IRQn         */
	USB_WAKEUP_IRQn               = 30,		/*!< USB wake-up interrupt Interrupt                  */
	ADC0_SEQA_IRQn                = 31,		/*!< ADC0_A sequencer Interrupt                       */
	ADC0_A_IRQn                   = ADC0_SEQA_IRQn,	/*!< Optional alias for ADC0_SEQA_IRQn        */
	ADC_A_IRQn                    = ADC0_SEQA_IRQn,	/*!< Optional alias for ADC0_SEQA_IRQn        */
	ADC0_SEQB_IRQn                = 32,		/*!< ADC0_B sequencer Interrupt                       */
	ADC0_B_IRQn                   = ADC0_SEQB_IRQn,	/*!< Optional alias for ADC0_SEQB_IRQn        */
	ADC_B_IRQn                    = ADC0_SEQB_IRQn,	/*!< Optional alias for ADC0_SEQB_IRQn        */
	ADC0_THCMP                    = 33,		/*!< ADC0 threshold compare interrupt                 */
	ADC0_OVR                      = 34,		/*!< ADC0 overrun interrupt                           */
	ADC1_SEQA_IRQn                = 35,		/*!< ADC1_A sequencer Interrupt                       */
	ADC1_A_IRQn                   = ADC1_SEQA_IRQn,	/*!< Optional alias for ADC1_SEQA_IRQn        */
	ADC1_SEQB_IRQn                = 36,		/*!< ADC1_B sequencer Interrupt                       */
	ADC1_B_IRQn                   = ADC1_SEQB_IRQn,	/*!< Optional alias for ADC1_SEQB_IRQn        */
	ADC1_THCMP                    = 37,		/*!< ADC1 threshold compare interrupt                 */
	ADC1_OVR                      = 38,		/*!< ADC1 overrun interrupt                           */
	DAC_IRQ                       = 39,		/*!< DAC interrupt                                    */
	CMP0_IRQ                      = 40,		/*!< Analog comparator 0 interrupt                    */
	CMP_IRQn                      = CMP0_IRQ,	/*!< Optional alias for CMP0_IRQ                    */
	CMP1_IRQ                      = 41,		/*!< Analog comparator 1 interrupt                    */
	CMP2_IRQ                      = 42,		/*!< Analog comparator 2 interrupt                    */
	CMP3_IRQ                      = 43,		/*!< Analog comparator 3 interrupt                    */
	QEI_IRQn                      = 44,		/*!< QEI interrupt                                    */
	RTC_ALARM_IRQn                = 45,		/*!< RTC alarm interrupt                              */
	RTC_WAKE_IRQn                 = 46,		/*!< RTC wake-up interrupt                            */
} IRQn_Type;


/*
 * ==========================================================================
 * ----------- Processor and Core Peripheral Section ------------------------
 * ==========================================================================
 */

/** @defgroup CMSIS_15XX_COMMON CHIP: LPC15xx Cortex CMSIS definitions
 * @{
 */

#define __CM3_REV               0x0201		/*!< Cortex-M3 Core Revision                          */
#define __MPU_PRESENT             0			/*!< MPU present or not                    */
#define __NVIC_PRIO_BITS          3			/*!< Number of Bits used for Priority Levels */
#define __Vendor_SysTickConfig    0			/*!< Set to 1 if different SysTick Config is used */
#define __FPU_PRESENT             0			/*!< FPU present or not                    */

/**
 * @}
 */

#include "../core/core_cm3.h"

/******************************************************************************/
/*                Device Specific Peripheral registers structures             */
/******************************************************************************/

#if defined(__ARMCC_VERSION)
// Kill warning "#pragma push with no matching #pragma pop"
  #pragma diag_suppress 2525
  #pragma push
  #pragma anon_unions
#elif defined(__CWCC__)
  #pragma push
  #pragma cpp_extensions on
#elif defined(__GNUC__)
/* anonymous unions are enabled by default */
#elif defined(__IAR_SYSTEMS_ICC__)
//  #pragma push // FIXME not usable for IAR
  #pragma language=extended
#else
  #error Not supported compiler type
#endif

#include "lpc15xx/romapi_15xx.h"

/**
 * @brief LPC15XX System Control block structure
 */
typedef struct {					/*!< SYSCTL Structure */
	__IO uint32_t  SYSMEMREMAP;		/*!< System Memory remap register */
	__I  uint32_t  RESERVED0[2];
	__IO uint32_t  AHBBUFEN0;		
	__IO uint32_t  AHBBUFEN1;		
	__IO uint32_t  SYSTCKCAL;		/*!< System tick counter calibration register */
	__I  uint32_t  RESERVED1[1];
	__IO uint32_t  NMISRC;			/*!< NMI source control register */
	__I  uint32_t  RESERVED2[8];
	__IO uint32_t  SYSRSTSTAT;		/*!< System Reset Status register */
	__IO uint32_t  PRESETCTRL[2];	/*!< Peripheral reset Control registers */
	__I  uint32_t  PIOPORCAP[3];	/*!< POR captured PIO status registers */
	__I  uint32_t  RESERVED3[10];
	__IO uint32_t  MAINCLKSELA;		/*!< Main clock source A select register */
	__IO uint32_t  MAINCLKSELB;		/*!< Main clock source B select register */
	__IO uint32_t  USBCLKSEL;		/*!< USB clock source select register */
	__IO uint32_t  ADCASYNCCLKSEL;	/*!< ADC asynchronous clock source select register */
	__I  uint32_t  RESERVED4[1];
	__IO uint32_t  CLKOUTSEL[2];	/*!< Clock out source select registers */
	__I  uint32_t  RESERVED5[1];
	__IO uint32_t  SYSPLLCLKSEL;	/*!< System PLL clock source select register */
	__IO uint32_t  USBPLLCLKSEL;	/*!< USB PLL clock source select register */
	__IO uint32_t  SCTPLLCLKSEL;	/*!< SCT PLL clock source select register */
	__I  uint32_t  RESERVED6[5];
	__IO uint32_t  SYSAHBCLKDIV;	/*!< System Clock divider register */
	__IO uint32_t  SYSAHBCLKCTRL[2];/*!< System clock control registers */
	__IO uint32_t  SYSTICKCLKDIV;	/*!< SYSTICK clock divider */
	__IO uint32_t  UARTCLKDIV;		/*!< UART clock divider register */
	__IO uint32_t  IOCONCLKDIV;		/*!< programmable glitch filter divider registers for IOCON */
	__IO uint32_t  TRACECLKDIV;		/*!< ARM trace clock divider register */
	__I  uint32_t  RESERVED7[4];
	__IO uint32_t  USBCLKDIV;		/*!< USB clock source divider register */
	__IO uint32_t  ADCASYNCCLKDIV;	/*!< Asynchronous ADC clock divider */
	__I  uint32_t  RESERVED8[1];
	__IO uint32_t  CLKOUTDIV;		/*!< Clock out divider register */
	__I  uint32_t  RESERVED9[9];
	__IO uint32_t  FREQMECTRL;		/*!< Frequency measure register */
	__IO uint32_t  FLASHCFG;		/*!< Flash configuration register */
	__IO uint32_t  FRGCTRL;			/*!< USART fractional baud rate generator control register */
	__IO uint32_t  USBCLKCTRL;		/*!< USB clock control register */
	__I  uint32_t  USBCLKST;		/*!< USB clock status register */
	__I  uint32_t  RESERVED10[19];
	__IO uint32_t  BODCTRL;			/*!< Brown Out Detect register */
	__I  uint32_t  IRCCTRL;			
	__IO uint32_t  SYSOSCCTRL;		/*!< System Oscillator control register */
	__I  uint32_t  RESERVED11[1];
	__IO uint32_t  RTCOSCCTRL;		/*!< RTC Oscillator control register */
	__I  uint32_t  RESERVED12[1];
	__IO uint32_t  SYSPLLCTRL;		/*!< System PLL control register */
	__I  uint32_t  SYSPLLSTAT;		/*!< System PLL status register */
	__IO uint32_t  USBPLLCTRL;		/*!< USB PLL control register */
	__I  uint32_t  USBPLLSTAT;		/*!< USB PLL status register */
	__IO uint32_t  SCTPLLCTRL;		/*!< SCT PLL control register */
	__I  uint32_t  SCTPLLSTAT;		/*!< SCT PLL status register */
	__I  uint32_t  RESERVED13[21];
	__IO uint32_t  PDWAKECFG;		/*!< Power down states in wake up from deep sleep register */
	__IO uint32_t  PDRUNCFG;		/*!< Power configuration register*/
	__I  uint32_t  RESERVED14[3];
	__IO uint32_t  STARTERP[2];		/*!< Start logic interrupt wake-up enable registers */
	__I  uint32_t  RESERVED15[117];
	__I  uint32_t  JTAG_IDCODE;		/*!< JTAG ID code register */
	__I  uint32_t  DEVICEID[2];		/*!< Device ID registers */
} LPC_SYSCTL_T;


/**
 * @brief LPC15XX IO Configuration Unit register block structure
 */
typedef struct {			/*!< LPC15XX IOCON Structure */
	__IO uint32_t  PIO[3][32];
} LPC_IOCON_T;


/**
 * @brief LPC15XX Switch Matrix register block structure
 */
typedef struct {
	__IO uint32_t PINASSIGN[16];	/*!< Pin Assignment register array */
	__I  uint32_t RESERVED0[96];
	__IO uint32_t PINENABLE[2];		/*!< fixed pin enable/disable registers */
} LPC_SWM_T;


/**
 * @brief LPC15xx Power Management Unit register block structure
 */
typedef struct {
	__IO uint32_t PCON;		/*!< Offset: 0x000 Power control Register (R/W) */
	__IO uint32_t GPREG[5];	/*!< Offset: 0x004 General purpose Registers 0..4 (R/W) */
} LPC_PMU_T;


/**
 * @brief  GPIO port register block structure
 */
typedef struct {				/*!< GPIO_PORT Structure */
	__IO uint8_t B[128][32];	/*!< Offset 0x0000: Byte pin registers ports 0 to n; pins PIOn_0 to PIOn_31 */
	__IO uint32_t W[32][32];	/*!< Offset 0x1000: Word pin registers port 0 to n */
	__IO uint32_t DIR[32];		/*!< Offset 0x2000: Direction registers port n */
	__IO uint32_t MASK[32];		/*!< Offset 0x2080: Mask register port n */
	__IO uint32_t PIN[32];		/*!< Offset 0x2100: Portpin register port n */
	__IO uint32_t MPIN[32];		/*!< Offset 0x2180: Masked port register port n */
	__IO uint32_t SET[32];		/*!< Offset 0x2200: Write: Set register for port n Read: output bits for port n */
	__O  uint32_t CLR[32];		/*!< Offset 0x2280: Clear port n */
	__O  uint32_t NOT[32];		/*!< Offset 0x2300: Toggle port n */
} LPC_GPIO_T;


/**
 * @brief LPC15xx Pin Interrupt and Pattern Match register block structure
 */
typedef struct {			/*!< PIN_INT Structure */
	__IO uint32_t ISEL;		/*!< Pin Interrupt Mode register */
	__IO uint32_t IENR;		/*!< Pin Interrupt Enable (Rising) register */
	__IO uint32_t SIENR;	/*!< Set Pin Interrupt Enable (Rising) register */
	__IO uint32_t CIENR;	/*!< Clear Pin Interrupt Enable (Rising) register */
	__IO uint32_t IENF;		/*!< Pin Interrupt Enable Falling Edge / Active Level register */
	__IO uint32_t SIENF;	/*!< Set Pin Interrupt Enable Falling Edge / Active Level register */
	__IO uint32_t CIENF;	/*!< Clear Pin Interrupt Enable Falling Edge / Active Level address */
	__IO uint32_t RISE;		/*!< Pin Interrupt Rising Edge register */
	__IO uint32_t FALL;		/*!< Pin Interrupt Falling Edge register */
	__IO uint32_t IST;		/*!< Pin Interrupt Status register */
} LPC_PIN_INT_T;


/**
 * @brief GPIO grouped interrupt register block structure
 */
typedef struct {					/*!< GPIO_GROUP_INTn Structure */
	__IO uint32_t  CTRL;			/*!< GPIO grouped interrupt control register */
	__I  uint32_t  RESERVED0[7];
	__IO uint32_t  PORT_POL[8];		/*!< GPIO grouped interrupt port polarity register */
	__IO uint32_t  PORT_ENA[8];		/*!< GPIO grouped interrupt port m enable register */
	uint32_t       RESERVED1[1000];
} LPC_GPIOGROUPINT_T;


/**
 * @brief UART register block structure
 */
typedef struct {
	__IO uint32_t  CFG;				/*!< Configuration register */
	__IO uint32_t  CTRL;			/*!< Control register */
	__IO uint32_t  STAT;			/*!< Status register */
	__IO uint32_t  INTENSET;		/*!< Interrupt Enable read and set register */
	__O  uint32_t  INTENCLR;		/*!< Interrupt Enable clear register */
	__I  uint32_t  RXDATA;			/*!< Receive Data register */
	__I  uint32_t  RXDATA_STAT;		/*!< Receive Data with status register */
	__IO uint32_t  TXDATA;			/*!< Transmit data register */
	__IO uint32_t  BRG;				/*!< Baud Rate Generator register */
	__IO uint32_t  INTSTAT;			/*!< Interrupt status register */
} LPC_USART_T;


/** Sequence index enumerations, used in various parts of the code for
    register indexing and sequencer selection */
typedef enum {
	ADC_SEQA_IDX,
	ADC_SEQB_IDX
} ADC_SEQ_IDX_T;

/**
 * @brief ADC register block structure
 */
typedef struct {								/*!< ADCn Structure */
	__IO uint32_t CTRL;							/*!< A/D Control Register. The AD0CR register must be written to select the operating mode before A/D conversion can occur. */
	__IO uint32_t INSEL;						/*!< A/D Input Select Register. This field selects the input source for channel 0. */
	__IO uint32_t SEQ_CTRL[ADC_SEQB_IDX + 1];	/*!< A/D Sequence A & B Control Register. Controls triggering and channel selection for sonversion sequence. */
	__IO uint32_t SEQ_GDAT[ADC_SEQB_IDX + 1];	/*!< A/D Sequence A & B Global Data Register. Contains the result of the most recent A/D conversion for sequence. */
	__I  uint32_t RESERVED1[2];
	__I  uint32_t DR[12];						/*!< A/D Channel Data Register. This register contains the result of the most recent conversion completed on channel n. */
	__IO uint32_t THR_LOW[2];					/*!< A/D Low Compare Threshold Register 0 & 1. Contains the lower threshold level for automatic threshold comparison. */
	__IO uint32_t THR_HIGH[2];					/*!< A/D High Compare Threshold Register 0 & 1. Contains the higher threshold level for automatic threshold comparison. */
	__IO uint32_t CHAN_THRSEL;					/*!< A/D Channel Threshold Select Register. Specifies which set of threshold compare registers to use. */
	__IO uint32_t INTEN;						/*!< A/D Interrupt Enable Register. This register contains enable bits that enable sequence-A, sequence-B, threshold compare and overrun interrupts. */
	__IO uint32_t FLAGS;						/*!< A/D Flags Register. This register contains interrupt flags. - To be checked */
	__IO uint32_t TRM;							/*!< A/D Trim Register. */
} LPC_ADC_T;


/**
 * @brief LPC15xx MRT chip configuration
 */
#define MRT_CHANNELS_NUM      (4)
#define MRT_NO_IDLE_CHANNEL   (0x40)

/**
 * @brief MRT register block structure
 */
typedef struct {
	__IO uint32_t INTVAL;	/*!< Timer interval register */
	__O  uint32_t TIMER;	/*!< Timer register */
	__IO uint32_t CTRL;		/*!< Timer control register */
	__IO uint32_t STAT;		/*!< Timer status register */
} LPC_MRT_CH_T;

/**
 * @brief MRT register block structure
 */
typedef struct {
	LPC_MRT_CH_T CHANNEL[MRT_CHANNELS_NUM];
	uint32_t unused[45];
	__O  uint32_t IDLE_CH;
	__IO uint32_t IRQ_FLAG;
} LPC_MRT_T;


/**
 * @brief Repetitive Interrupt Timer register block structure
 */
typedef struct {				/*!< RITIMER Structure      */
	__IO uint32_t  COMPVAL;		/*!< Compare register       */
	__IO uint32_t  MASK;		/*!< Mask register. This register holds the 32-bit mask value. A 1 written to any bit will force a compare on the corresponding bit of the counter and compare register. */
	__IO uint32_t  CTRL;		/*!< Control register       */
	__IO uint32_t  COUNTER;		/*!< 32-bit counter         */
	__IO uint32_t  COMPVAL_H;	/*!< Compare upper register */
	__IO uint32_t  MASK_H;		/*!< Mask upper register    */
	__I  uint32_t  RESERVED0[1];
	__IO uint32_t  COUNTER_H;	/*!< Counter upper register */
} LPC_RITIMER_T;


/**
 * @brief DMA Controller shared registers structure
 */
typedef struct {					/*!< DMA shared registers structure */
	__IO uint32_t  ENABLESET;		/*!< DMA Channel Enable read and Set for all DMA channels */
	__I  uint32_t  RESERVED0;
	__O  uint32_t  ENABLECLR;		/*!< DMA Channel Enable Clear for all DMA channels */
	__I  uint32_t  RESERVED1;
	__I  uint32_t  ACTIVE;			/*!< DMA Channel Active status for all DMA channels */
	__I  uint32_t  RESERVED2;
	__I  uint32_t  BUSY;			/*!< DMA Channel Busy status for all DMA channels */
	__I  uint32_t  RESERVED3;
	__IO uint32_t  ERRINT;			/*!< DMA Error Interrupt status for all DMA channels */
	__I  uint32_t  RESERVED4;
	__IO uint32_t  INTENSET;		/*!< DMA Interrupt Enable read and Set for all DMA channels */
	__I  uint32_t  RESERVED5;
	__O  uint32_t  INTENCLR;		/*!< DMA Interrupt Enable Clear for all DMA channels */
	__I  uint32_t  RESERVED6;
	__IO uint32_t  INTA;			/*!< DMA Interrupt A status for all DMA channels */
	__I  uint32_t  RESERVED7;
	__IO uint32_t  INTB;			/*!< DMA Interrupt B status for all DMA channels */
	__I  uint32_t  RESERVED8;
	__O  uint32_t  SETVALID;		/*!< DMA Set ValidPending control bits for all DMA channels */
	__I  uint32_t  RESERVED9;
	__O  uint32_t  SETTRIG;			/*!< DMA Set Trigger control bits for all DMA channels */
	__I  uint32_t  RESERVED10;
	__O  uint32_t  ABORT;			/*!< DMA Channel Abort control for all DMA channels */
} LPC_DMA_COMMON_T;

/**
 * @brief DMA Controller shared registers structure
 */
typedef struct {					/*!< DMA channel register structure */
	__IO uint32_t  CFG;				/*!< DMA Configuration register */
	__I  uint32_t  CTLSTAT;			/*!< DMA Control and status register */
	__IO uint32_t  XFERCFG;			/*!< DMA Transfer configuration register */
	__I  uint32_t  RESERVED;
} LPC_DMA_CHANNEL_T;

/* DMA channel mapping - each channel is mapped to an individual peripheral
   and direction or a DMA imput mux trigger */
typedef enum {
	DMAREQ_USART0_RX = 0,					/*!< USART0 receive DMA channel */
	DMA_CH0 = DMAREQ_USART0_RX,
	DMAREQ_USART0_TX,						/*!< USART0 transmit DMA channel */
	DMA_CH1 = DMAREQ_USART0_TX,
	DMAREQ_USART1_RX,						/*!< USART1 receive DMA channel */
	DMA_CH2 = DMAREQ_USART1_RX,
	DMAREQ_USART1_TX,						/*!< USART1 transmit DMA channel */
	DMA_CH3 = DMAREQ_USART1_TX,
	DMAREQ_USART2_RX,						/*!< USART2 receive DMA channel */
	DMA_CH4 = DMAREQ_USART2_RX,
	DMAREQ_USART2_TX,						/*!< USART2 transmit DMA channel */
	DMA_CH5 = DMAREQ_USART2_TX,
	DMAREQ_SPI0_RX,							/*!< SSP0 receive DMA channel */
	DMA_CH6 = DMAREQ_SPI0_RX,
	DMAREQ_SPI0_TX,							/*!< SSP0 transmit DMA channel */
	DMA_CH7 = DMAREQ_SPI0_TX,
	DMAREQ_SPI1_RX,							/*!< SSP1 receive DMA channel */
	DMA_CH8 = DMAREQ_SPI1_RX,
	DMAREQ_SPI1_TX,							/*!< SSP1 transmit DMA channel */
	DMA_CH9 = DMAREQ_SPI1_TX,
	DMAREQ_I2C0_SLV,						/*!< I2C0 slave DMA channel */
	DMA_CH10 = DMAREQ_I2C0_SLV,
	DMAREQ_I2C0_MST,						/*!< I2C0 master DMA channel */
	DMA_CH11 = DMAREQ_I2C0_MST,
	DMAREQ_I2C0_MONITOR,					/*!< I2C0 monitor DMA channel */
	DMA_CH12 = DMAREQ_I2C0_MONITOR,
	DMAREQ_DAC_IRQ,							/*!< DAC DMA channel */
	DMA_CH13 = DMAREQ_DAC_IRQ,
	DMAREQ_RESERVED_14,
	DMA_CH14 = DMAREQ_RESERVED_14,
	DMAREQ_RESERVED_15,
	DMA_CH15 = DMAREQ_RESERVED_15,
	DMAREQ_RESERVED_16,
	DMA_CH16 = DMAREQ_RESERVED_16,
	DMAREQ_RESERVED_17,
	DMA_CH17 = DMAREQ_RESERVED_17
} DMA_CHID_T;

/* On LPC15xx, Max DMA channel is 18 */
#define MAX_DMA_CHANNEL         (DMA_CH17 + 1)

/**
 * @brief DMA Controller register block structure
 */
typedef struct {					/*!< DMA Structure */
	__IO uint32_t  CTRL;			/*!< DMA control register */
	__I  uint32_t  INTSTAT;			/*!< DMA Interrupt status register */
	__IO uint32_t  SRAMBASE;		/*!< DMA SRAM address of the channel configuration table */
	__I  uint32_t  RESERVED2[5];
	LPC_DMA_COMMON_T DMACOMMON[1];	/*!< DMA shared channel (common) registers */
	__I  uint32_t  RESERVED0[225];
	LPC_DMA_CHANNEL_T DMACH[MAX_DMA_CHANNEL];	/*!< DMA channel registers */
} LPC_DMA_T;


/**
 * @brief LPC15XX SCTIPU abort enable/source register block structure
 */
typedef struct {			/*!< LPC15XX abort enable/source structure */
	__IO uint32_t  ABORT_ENABLE;	/*!< SCTIPU abort enable register */
	__IO uint32_t  ABORT_SOURCE;	/*!< SCTIPU abort source register */
	__I  uint32_t  RESERVED[6];
} LPC_SCTIPU_ABT_T;


/**
 * @brief USB device register block structure
 */
typedef struct {				/*!< USB Structure */
	__IO uint32_t DEVCMDSTAT;	/*!< USB Device Command/Status register */
	__IO uint32_t INFO;			/*!< USB Info register */
	__IO uint32_t EPLISTSTART;	/*!< USB EP Command/Status List start address */
	__IO uint32_t DATABUFSTART;	/*!< USB Data buffer start address */
	__IO uint32_t LPM;			/*!< Link Power Management register */
	__IO uint32_t EPSKIP;		/*!< USB Endpoint skip */
	__IO uint32_t EPINUSE;		/*!< USB Endpoint Buffer in use */
	__IO uint32_t EPBUFCFG;		/*!< USB Endpoint Buffer Configuration register */
	__IO uint32_t INTSTAT;		/*!< USB interrupt status register */
	__IO uint32_t INTEN;		/*!< USB interrupt enable register */
	__IO uint32_t INTSETSTAT;	/*!< USB set interrupt status register */
	__IO uint32_t INTROUTING;	/*!< USB interrupt routing register */
	__I  uint32_t RESERVED0[1];
	__I  uint32_t EPTOGGLE;		/*!< USB Endpoint toggle register */
} LPC_USB_T;


/**
 * @brief LPC15XX SCTIPU register block structure
 */
typedef struct {			/*!< LPC15XX SCTIPU Structure */
	__IO uint32_t  SAMPLE_CTRL;	/*!< SCTIPU sample control register */
	__I  uint32_t  RESERVED[7];
	LPC_SCTIPU_ABT_T ABORT[4];	/*!< SCTIPU abort enable/source registers */
} LPC_SCTIPU_T;


/**
 * @brief LPC15xx Pin Interrupt and Pattern Match register block structure
 */
typedef struct {			/*!< RTC */
	__IO uint32_t CTRL;		/*!< RTC control register */
	__IO uint32_t MATCH;	/*!< PRTC match (alarm) register */
	__IO uint32_t COUNT;	/*!< RTC counter register */
	__IO uint32_t WAKE;		/*!< RTC high-resolution/wake-up timer control register */
} LPC_RTC_T;


/**
 * @brief Windowed Watchdog register block structure
 */
typedef struct {				/*!< WWDT Structure         */
	__IO uint32_t  MOD;			/*!< Watchdog mode register. This register contains the basic mode and status of the Watchdog Timer. */
	__IO uint32_t  TC;			/*!< Watchdog timer constant register. This register determines the time-out value. */
	__O  uint32_t  FEED;		/*!< Watchdog feed sequence register. Writing 0xAA followed by 0x55 to this register reloads the Watchdog timer with the value contained in WDTC. */
	__I  uint32_t  TV;			/*!< Watchdog timer value register. This register reads out the current value of the Watchdog timer. */
	__IO uint32_t  RESERVED;
	__IO uint32_t  WARNINT;		/*!< Watchdog warning interrupt register. This register contains the Watchdog warning interrupt compare value. */
	__IO uint32_t  WINDOW;		/*!< Watchdog timer window register. This register contains the Watchdog window value. */
} LPC_WWDT_T;


/**
 * @brief FLASH Memory Controller Unit register block structure
 */
typedef struct {		/*!< FMC Structure */
	__I  uint32_t  RESERVED1[7];
	__IO uint32_t  FMSSTART;
	__IO uint32_t  FMSSTOP;
	__I  uint32_t  RESERVED2;
	__I  uint32_t  FMSW[1];
} LPC_FMC_T;


/**
 * @brief LPC15xx Input Mux Register Block Structure
 */
typedef struct {						/*!< INMUX Structure */
	__IO uint32_t SCT0_INMUX[7];		/*!< Input mux registers for SCT0 inputs */
	__I  uint32_t  RESERVED1[1];
	__IO uint32_t SCT1_INMUX[7];		/*!< Input mux registers for SCT1 inputs */
	__I  uint32_t  RESERVED2[1];
	__IO uint32_t SCT2_INMUX[3];		/*!< Input mux registers for SCT2 inputs */
	__I  uint32_t  RESERVED3[5];
	__IO uint32_t SCT3_INMUX[3];		/*!< Input mux registers for SCT3 inputs */
	__I  uint32_t  RESERVED4[5];
	__I  uint32_t  RESERVED4A[16];
	__IO uint32_t PINTSEL[8];			/*!< Pin interrupt select registers */
	__IO uint32_t DMA_ITRIG_INMUX[18];	/*!< Input mux register for DMA trigger inputs */
	__I  uint32_t  RESERVED5[6];
	__IO uint32_t DMA_INMUX[4];			/*!< Input mux register for DMA trigger inputs */
	__I  uint32_t  RESERVED6[4];
	__IO uint32_t FREQMEAS_REF;			/*!< Clock selection for frequency measurement ref clock */
	__IO uint32_t FREQMEAS_TARGET;		/*!< Clock selection for frequency measurement target clock */
} LPC_INMUX_T;


/**
 * @brief Analog Comparator channel register block structure
 */
typedef struct {
	__IO uint32_t  CMP;			/*!< Individual Comparator control register */
	__IO uint32_t  CMPFILTR;	/*!< Individual Comparator Filter registers */
} CMP_REG_T;

/**
 * @brief Analog Comparator register block structure
 */
typedef struct {					/*!< ACMP Structure */
	__IO uint32_t  CTRL;		/*!< Comparator block control register */
	__IO CMP_REG_T ACMP[4];		/*!< Individual Comparator registers */
} LPC_CMP_T;


/**
 * @brief DAC register block structure
 */
typedef struct {				/*!< DAC Structure */
	__IO uint32_t  VAL;		/*!< DAC register. Holds the conversion data */
	__IO uint32_t  CTRL;	/*!< DAC control register */
	__IO uint32_t  CNTVAL;	/*!< DAC counter value register */
} LPC_DAC_T;


/**
 * @brief SPI register block structure
 */
typedef struct {					/*!< SPI Structure */
	__IO uint32_t  CFG;				/*!< SPI Configuration register*/
	__IO uint32_t  DLY;				/*!< SPI Delay register*/
	__IO uint32_t  STAT;			/*!< SPI Status. register*/
	__IO uint32_t  INTENSET;		/*!< SPI Interrupt Enable.Set register*/
	__O  uint32_t  INTENCLR;		/*!< SPI Interrupt Enable Clear. register*/
	__I  uint32_t  RXDAT;			/*!< SPI Receive Data register*/
	__IO uint32_t  TXDATCTL;		/*!< SPI Transmit Data with Control register*/
	__IO uint32_t  TXDAT;			/*!< SPI Transmit Data register*/
	__IO uint32_t  TXCTRL;			/*!< SPI Transmit Control register*/
	__IO uint32_t  DIV;				/*!< SPI clock Divider register*/
	__I  uint32_t  INTSTAT;			/*!< SPI Interrupt Status register*/
} LPC_SPI_T;


/**
 * @brief I2C register block structure
 */
typedef struct {					/* I2C0 Structure         */
	__IO uint32_t CFG;			/*!< I2C Configuration Register common for Master, Slave and Monitor */
	__IO uint32_t STAT;			/*!< I2C Status Register common for Master, Slave and Monitor */
	__IO uint32_t INTENSET;	/*!< I2C Interrupt Enable Set Register common for Master, Slave and Monitor */
	__O  uint32_t INTENCLR;	/*!< I2C Interrupt Enable Clear Register common for Master, Slave and Monitor */
	__IO uint32_t TIMEOUT;	/*!< I2C Timeout value Register */
	__IO uint32_t CLKDIV;		/*!< I2C Clock Divider Register */
	__I  uint32_t INTSTAT;	/*!< I2C Interrupt Status Register */
	__I  uint32_t RESERVED0;
	__IO uint32_t MSTCTL;		/*!< I2C Master Control Register */
	__IO uint32_t MSTTIME;	/*!< I2C Master Time Register for SCL */
	__IO uint32_t MSTDAT;		/*!< I2C Master Data Register */
	__I  uint32_t RESERVED1[5];
	__IO uint32_t SLVCTL;		/*!< I2C Slave Control Register */
	__IO uint32_t SLVDAT;		/*!< I2C Slave Data Register */
	__IO uint32_t SLVADR[4];	/*!< I2C Slave Address Registers */
	__IO uint32_t SLVQUAL0;	/*!< I2C Slave Address Qualifier 0 Register */
	__I  uint32_t RESERVED2[9];
	__I  uint32_t MONRXDAT;	/*!< I2C Monitor Data Register */
} LPC_I2C_T;




/** @defgroup PERIPH_15XX_BASE CHIP: LPC15xx Peripheral addresses and register set declarations
 * @ingroup CHIP_15XX_Drivers
 * @{
 */

#define LPC_ADC0_BASE             0x40000000
#define LPC_DAC_BASE              0x40004000
#define LPC_CMP_BASE              0x40008000
#define LPC_INMUX_BASE            0x40014000
#define LPC_RTC_BASE              0x40028000
#define LPC_WWDT_BASE             0x4002C000
#define LPC_SWM_BASE              0x40038000
#define LPC_PMU_BASE              0x4003C000
#define LPC_USART0_BASE           0x40040000
#define LPC_USART1_BASE           0x40044000
#define LPC_SPI0_BASE             0x40048000
#define LPC_SPI1_BASE             0x4004C000
#define LPC_I2C_BASE              0x40050000
#define LPC_QEI_BASE              0x40058000
#define LPC_SYSCTL_BASE           0x40074000
#define LPC_ADC1_BASE             0x40080000
#define LPC_MRT_BASE              0x400A0000
#define LPC_PIN_INT_BASE          0x400A4000
#define LPC_GPIO_GROUP_INT0_BASE  0x400A8000
#define LPC_GPIO_GROUP_INT1_BASE  0x400AC000
#define LPC_RITIMER_BASE          0x400B4000
#define LPC_SCTIPU_BASE           0x400B8000
#define LPC_FLASH_BASE            0x400BC000
#define LPC_USART2_BASE           0x400C0000
#define TBD_BASE                  0x400E8000
#define LPC_C_CAN0_BASE           0x400F0000
#define LPC_IOCON_BASE            0x400F8000
#define LPC_EEPROM_BASE           0x400FC000
#define LPC_GPIO_PIN_INT_BASE     0x1C000000
#define LPC_DMA_BASE              0x1C004000
#define LPC_USB0_BASE             0x1C00C000
#define LPC_CRC_BASE              0x1C010000
#define LPC_SCTLARGE_0_BASE       0x1C018000
#define LPC_SCTLARGE_1_BASE       0x1C01C000
#define LPC_SCTSMALL_0_BASE       0x1C020000
#define LPC_SCTSMALL_1_BASE       0x1C024000

#define LPC_PMU                   ((LPC_PMU_T              *) LPC_PMU_BASE)
#define LPC_IOCON                 ((LPC_IOCON_T            *) LPC_IOCON_BASE)
#define LPC_SYSCTL                ((LPC_SYSCTL_T           *) LPC_SYSCTL_BASE)
#define LPC_SYSCON                ((LPC_SYSCTL_T           *) LPC_SYSCTL_BASE)	/* Alias for LPC_SYSCTL */
#define LPC_GPIO                  ((LPC_GPIO_T             *) LPC_GPIO_PIN_INT_BASE)
#define LPC_GPIOGROUP             ((LPC_GPIOGROUPINT_T     *) LPC_GPIO_GROUP_INT0_BASE)
#define LPC_GPIO_PIN_INT          ((LPC_PIN_INT_T          *) LPC_PIN_INT_BASE)
#define LPC_USART0                ((LPC_USART_T            *) LPC_USART0_BASE)
#define LPC_USART1                ((LPC_USART_T            *) LPC_USART1_BASE)
#define LPC_USART2                ((LPC_USART_T            *) LPC_USART2_BASE)
#define LPC_I2C0                  ((LPC_I2C_T              *) LPC_I2C_BASE)
// #define LPC_I2C1                  ((LPC_I2C_T              *) LPC_I2C1_BASE)
// #define LPC_SSP0                  ((LPC_SSP_T              *) LPC_SSP0_BASE)
// #define LPC_SSP1                  ((LPC_SSP_T              *) LPC_SSP1_BASE)
#define LPC_USB                   ((LPC_USB_T              *) LPC_USB0_BASE)
#define LPC_ADC0                  ((LPC_ADC_T              *) LPC_ADC0_BASE)
#define LPC_ADC1                  ((LPC_ADC_T              *) LPC_ADC1_BASE)
// #define LPC_SCT0                  ((LPC_SCT_T              *) LPC_SCT0_BASE)
// #define LPC_SCT1                  ((LPC_SCT_T              *) LPC_SCT1_BASE)
// #define LPC_TIMER16_0             ((LPC_TIMER_T            *) LPC_TIMER16_0_BASE)
// #define LPC_TIMER16_1             ((LPC_TIMER_T            *) LPC_TIMER16_1_BASE)
// #define LPC_TIMER32_0             ((LPC_TIMER_T            *) LPC_TIMER32_0_BASE)
// #define LPC_TIMER32_1             ((LPC_TIMER_T            *) LPC_TIMER32_1_BASE)
#define LPC_RTC                   ((LPC_RTC_T              *) LPC_RTC_BASE)
#define LPC_WWDT                  ((LPC_WWDT_T             *) LPC_WWDT_BASE)
#define LPC_DMA                   ((LPC_DMA_T              *) LPC_DMA_BASE)
#define LPC_CRC                   ((LPC_CRC_T              *) LPC_CRC_BASE)
#define LPC_FMC                   ((LPC_FMC_T              *) LPC_FLASH_BASE)
#define LPC_MRT                   ((LPC_MRT_T              *) LPC_MRT_BASE)
#define LPC_SWM                   ((LPC_SWM_T              *) LPC_SWM_BASE)
#define LPC_RITIMER               ((LPC_RITIMER_T          *) LPC_RITIMER_BASE)
#define LPC_INMUX                 ((LPC_INMUX_T            *) LPC_INMUX_BASE)
#define LPC_SCTIPU                ((LPC_SCTIPU_T           *) LPC_SCTIPU_BASE)
#define LPC_CMP                   ((LPC_CMP_T              *) LPC_CMP_BASE)
#define LPC_DAC                   ((LPC_DAC_T              *) LPC_DAC_BASE)
#define LPC_SPI0                  ((LPC_SPI_T              *) LPC_SPI0_BASE)
#define LPC_SPI1                  ((LPC_SPI_T              *) LPC_SPI1_BASE)

/**
 * @}
 */


/******************************************************************************/
/*                         Alias for Libs-hardware                            */
/******************************************************************************/

#define UART0_IRQn              UART_IRQn
#define LPC_UART0_BASE          LPC_UART_BASE
#define LPC_UART0               LPC_UART
#define LPC_GPIO_TypeDef        LPC_GPIO_T

#ifdef __cplusplus
}
#endif

#endif  // __LPC13xx_H__
