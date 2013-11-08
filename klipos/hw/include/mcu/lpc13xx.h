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

#ifndef __LPC13xx_H__
#define __LPC13xx_H__

/*
 * ==========================================================================
 * ---------- Interrupt Number Definition -----------------------------------
 * ==========================================================================
 */

typedef enum IRQn
{
/******  Cortex-M3 Processor Exceptions Numbers ***************************************************/
  NonMaskableInt_IRQn           = -14,      /*!< 2 Non Maskable Interrupt                         */
  MemoryManagement_IRQn         = -12,      /*!< 4 Cortex-M3 Memory Management Interrupt          */
  BusFault_IRQn                 = -11,      /*!< 5 Cortex-M3 Bus Fault Interrupt                  */
  UsageFault_IRQn               = -10,      /*!< 6 Cortex-M3 Usage Fault Interrupt                */
  SVCall_IRQn                   = -5,       /*!< 11 Cortex-M3 SV Call Interrupt                   */
  DebugMonitor_IRQn             = -4,       /*!< 12 Cortex-M3 Debug Monitor Interrupt             */
  PendSV_IRQn                   = -2,       /*!< 14 Cortex-M3 Pend SV Interrupt                   */
  SysTick_IRQn                  = -1,       /*!< 15 Cortex-M3 System Tick Interrupt               */

/******  LPC13xx Specific Interrupt Numbers *******************************************************/
#ifdef MCU_IS_LPC1311
  WAKEUP0_IRQn                  = 0,        /*!< PIO0_0 All I/O pins can be used as wakeup source.       */
  WAKEUP1_IRQn                  = 1,        /*!< PIO0_1 There are 40 pins in total for LPC17xx           */
  WAKEUP2_IRQn                  = 2,        // PIO0 2
  WAKEUP3_IRQn                  = 3,        // PIO0 3
  WAKEUP4_IRQn                  = 4,        // PIO0 4 
  WAKEUP5_IRQn                  = 5,        // PIO0 5
  WAKEUP6_IRQn                  = 6,        // PIO0 6
  WAKEUP7_IRQn                  = 7,        // PIO0 7
  WAKEUP8_IRQn                  = 8,        // PIO0 8
  WAKEUP9_IRQn                  = 9,        // PIO0 9
  WAKEUP10_IRQn                 = 10,       // PIO0 10
  WAKEUP11_IRQn                 = 11,       // PIO0 11
  WAKEUP12_IRQn                 = 12,       // PIO1 0
  WAKEUP13_IRQn                 = 13,       // PIO1 1
  WAKEUP14_IRQn                 = 14,       // PIO1 2
  WAKEUP15_IRQn                 = 15,       // PIO1 3
  WAKEUP16_IRQn                 = 16,       // PIO1 4
  WAKEUP17_IRQn                 = 17,       // PIO1 5
  WAKEUP18_IRQn                 = 18,       // PIO1 6
  WAKEUP19_IRQn                 = 19,       // PIO1 7
  WAKEUP20_IRQn                 = 20,       // PIO1 8
  WAKEUP21_IRQn                 = 21,       // PIO1 9
  WAKEUP22_IRQn                 = 22,       // PIO1 10
  WAKEUP23_IRQn                 = 23,       // PIO1 11
  WAKEUP24_IRQn                 = 24,       // PIO2 0
  WAKEUP25_IRQn                 = 25,       // PIO2 1
  WAKEUP26_IRQn                 = 26,       // PIO2 2
  WAKEUP27_IRQn                 = 27,       // PIO2 3
  WAKEUP28_IRQn                 = 28,       // PIO2 4
  WAKEUP29_IRQn                 = 29,       // PIO2 5
  WAKEUP30_IRQn                 = 30,       // PIO2 6
  WAKEUP31_IRQn                 = 31,       // PIO2 7
  WAKEUP32_IRQn                 = 32,       // PIO2 8
  WAKEUP33_IRQn                 = 33,       // PIO2 9
  WAKEUP34_IRQn                 = 34,       // PIO2 10
  WAKEUP35_IRQn                 = 35,       // PIO2 11
  WAKEUP36_IRQn                 = 36,       // PIO3 0
  WAKEUP37_IRQn                 = 37,       // PIO3 1
  WAKEUP38_IRQn                 = 38,       // PIO3 2
  WAKEUP39_IRQn                 = 39,       // PIO3 3
  I2C_IRQn                      = 40,       /*!< I2C Interrupt                                    */
  TIMER_16_0_IRQn               = 41,       /*!< 16-bit Timer0 Interrupt                          */
  TIMER_16_1_IRQn               = 42,       /*!< 16-bit Timer1 Interrupt                          */
  TIMER_32_0_IRQn               = 43,       /*!< 32-bit Timer0 Interrupt                          */
  TIMER_32_1_IRQn               = 44,       /*!< 32-bit Timer1 Interrupt                          */
  SSP_IRQn                      = 45,       /*!< SSP0 Interrupt  - original name                                  */
  SSP0_IRQn                     = 45,       /*!< SSP0 Interrupt  - new name                                   */
  UART_IRQn                     = 46,       /*!< UART Interrupt                                   */
  USB_IRQn                      = 47,       /*!< USB Regular Interrupt                            */
  USB_FIQn                      = 48,       /*!< USB Fast Interrupt                               */
  ADC_IRQn                      = 49,       /*!< A/D Converter Interrupt                          */
  WDT_IRQn                      = 50,       /*!< Watchdog timer Interrupt                         */  
  BOD_IRQn                      = 51,       /*!< Brown Out Detect(BOD) Interrupt                  */
  RESERVED_IRQn                 = 52,       /*!< Reserved Interrupt                               */
  EINT3_IRQn                    = 53,       /*!< External Interrupt 3 Interrupt                   */
  EINT2_IRQn                    = 54,       /*!< External Interrupt 2 Interrupt                   */
  EINT1_IRQn                    = 55,       /*!< External Interrupt 1 Interrupt                   */
  EINT0_IRQn                    = 56,       /*!< External Interrupt 0 Interrupt                   */
#else
  FLEX_INT0_IRQn                = 0,        /*!< All I/O pins can be routed to below 8 interrupts. */
  FLEX_INT1_IRQn                = 1,
  FLEX_INT2_IRQn                = 2,
  FLEX_INT3_IRQn                = 3,
  FLEX_INT4_IRQn                = 4,   
  FLEX_INT5_IRQn                = 5,        
  FLEX_INT6_IRQn                = 6,        
  FLEX_INT7_IRQn                = 7,        
  GINT0_IRQn                    = 8,        /*!< Grouped Interrupt 0                              */
  GINT1_IRQn                    = 9,        /*!< Grouped Interrupt 1                              */
  Reserved0_IRQn                = 10,       /*!< Reserved Interrupt                               */
  Reserved1_IRQn                = 11,       
  Reserved2_IRQn                = 12,       
  Reserved3_IRQn                = 13,       
  SSP1_IRQn                     = 14,       /*!< SSP1 Interrupt                                   */
  I2C_IRQn                      = 15,       /*!< I2C Interrupt                                    */
  TIMER_16_0_IRQn               = 16,       /*!< 16-bit Timer0 Interrupt                          */
  TIMER_16_1_IRQn               = 17,       /*!< 16-bit Timer1 Interrupt                          */
  TIMER_32_0_IRQn               = 18,       /*!< 32-bit Timer0 Interrupt                          */
  TIMER_32_1_IRQn               = 19,       /*!< 32-bit Timer1 Interrupt                          */
  SSP0_IRQn                     = 20,       /*!< SSP0 Interrupt                                   */
  UART_IRQn                     = 21,       /*!< UART Interrupt                                   */
  USB_IRQn                      = 22,       /*!< USB IRQ Interrupt                                */
  USB_FIQn                      = 23,       /*!< USB FIQ Interrupt                                */
  ADC_IRQn                      = 24,       /*!< A/D Converter Interrupt                          */
  WDT_IRQn                      = 25,       /*!< Watchdog timer Interrupt                         */  
  BOD_IRQn                      = 26,       /*!< Brown Out Detect(BOD) Interrupt                  */
  FMC_IRQn                      = 27,       /*!< Flash Memory Controller Interrupt                */
  Reserved4_IRQn                = 28,       /*!< Reserved Interrupt                               */
  Reserved5_IRQn                = 29,       /*!< Reserved Interrupt                               */
  USBWakeup_IRQn                = 30,       /*!< USB wakeup Interrupt                             */
  Reserved6_IRQn                = 31,       /*!< Reserved Interrupt                               */    
#endif
} IRQn_Type;


/*
 * ==========================================================================
 * ----------- Processor and Core Peripheral Section ------------------------
 * ==========================================================================
 */

/* Configuration of the Cortex-M3 Processor and Core Peripherals */
#define __MPU_PRESENT             1         /*!< MPU present or not                               */
#define __NVIC_PRIO_BITS          3         /*!< Number of Bits used for Priority Levels          */
#define __Vendor_SysTickConfig    0         /*!< Set to 1 if different SysTick Config is used     */


#include "../core/core_cm3.h"                       /* Cortex-M3 processor and core peripherals           */
//#include "system_LPC13xx.h"                 /* System Header                                      */


/******************************************************************************/
/*                Device Specific Peripheral registers structures             */
/******************************************************************************/

#if defined ( __CC_ARM   )
#pragma anon_unions
#endif

typedef struct {
	__IO uint32_t  STARTAPR;		/*!< Start logic edge control register */
	__IO uint32_t  STARTER;			/*!< Start logic signal enable register */
	__IO uint32_t  STARTRSRCLR;		/*!< Start logic reset register */
	__IO uint32_t  STARTSR;			/*!< Start logic status register */
} LPC_SYSCTL_STARTST_T;

/*------------- System Control (SYSCON) --------------------------------------*/
typedef struct {			/*!< SYSCTL Structure */
	__IO uint32_t  SYSMEMREMAP;		/*!< System Memory remap register */
	__IO uint32_t  PRESETCTRL;		/*!< Peripheral reset Control register */
	__IO uint32_t  SYSPLLCTRL;		/*!< System PLL control register */
	__I  uint32_t  SYSPLLSTAT;		/*!< System PLL status register */
	__IO uint32_t  USBPLLCTRL;		/*!< USB PLL control register, LPC134x only */
	__I  uint32_t  USBPLLSTAT;		/*!< USB PLL status register, LPC134x only */
	__I  uint32_t  RESERVED1[2];
	__IO uint32_t  SYSOSCCTRL;		/*!< System Oscillator control register */
	__IO uint32_t  WDTOSCCTRL;		/*!< Watchdog Oscillator control register */
#if defined(MCU_IS_LPC1315)
	__I  uint32_t  RESERVED2[2];
#else
	__IO uint32_t  IRCCTRL;			/*!< IRC control register */
	__I  uint32_t  RESERVED2[1];
#endif

	__IO uint32_t  SYSRSTSTAT;		/*!< System Reset Status register           */
	__I  uint32_t  RESERVED3[3];
	__IO uint32_t  SYSPLLCLKSEL;	/*!< System PLL clock source select register */
#if defined(MCU_IS_LPC1315)
	__I  uint32_t  RESERVED4;
#else
	__IO uint32_t  SYSPLLCLKUEN;	/*!< System PLL clock source update enable register*/
#endif
	__IO uint32_t  USBPLLCLKSEL;	/*!< USB PLL clock source select register, LPC134x only */
#if defined(MCU_IS_LPC1315)
	__I  uint32_t  RESERVED4A[1];
#else
	__IO uint32_t  USBPLLCLKUEN;	/*!< USB PLL clock source update enable register, LPC1342/43 only */
#endif
	__I  uint32_t  RESERVED5[8];
	__IO uint32_t  MAINCLKSEL;		/*!< Main clock source select register		*/
#if defined(MCU_IS_LPC1315)
	__IO uint32_t  RESERVED6;
#else
	__IO uint32_t  MAINCLKUEN;		/*!< Main clock source update enable register	*/
#endif
	__IO uint32_t  SYSAHBCLKDIV;	/*!< System Clock divider register */
	__I  uint32_t  RESERVED6A;
	__IO uint32_t  SYSAHBCLKCTRL;	/*!< System Clock control register */
	__I  uint32_t  RESERVED7[4];
	__IO uint32_t  SSP0CLKDIV;		/*!< SSP0 clock divider register   */
	__IO uint32_t  USARTCLKDIV;		/*!< UART clock divider register   */
	__IO uint32_t  SSP1CLKDIV;		/*!< SSP1 clock divider register */
	__I  uint32_t  RESERVED8[3];
	__IO uint32_t  TRACECLKDIV;		/*!< ARM trace clock divider register */
	__IO uint32_t  SYSTICKCLKDIV;	/*!< SYSTICK clock divider register */
	__I  uint32_t  RESERVED9[3];
	__IO uint32_t  USBCLKSEL;		/*!< USB clock source select register, LPC134x only */
#if defined(MCU_IS_LPC1315)
	__I  uint32_t  RESERVED10;
#else
	__IO uint32_t  USBCLKUEN;		/*!< USB clock source update enable register, LPC1342/43 only */
#endif
	__IO uint32_t  USBCLKDIV;		/*!< USB clock source divider register, LPC134x only */
#if defined(MCU_IS_LPC1315)
	__I  uint32_t  RESERVED11[4];
#else
	__I  uint32_t  RESERVED11;
	__IO uint32_t  WDTCLKSEL;		/*!< WDT clock source select register, some parts only */
	__IO uint32_t  WDTCLKUEN;		/*!< WDT clock source update enable register, some parts only */
	__IO uint32_t  WDTCLKDIV;		/*!< WDT clock divider register, some parts only */
#endif
	__I  uint32_t  RESERVED13;
	__IO uint32_t  CLKOUTSEL;		/*!< Clock out source select register */
#if defined(MCU_IS_LPC1315)
	__I  uint32_t  RESERVED12;
#else
	__IO uint32_t  CLKOUTUEN;		/*!< Clock out source update enable register, not on LPC1311/13/42/43 only */
#endif
	__IO uint32_t  CLKOUTDIV;		/*!< Clock out divider register */
	__I  uint32_t  RESERVED14[5];
	__I  uint32_t  PIOPORCAP[2];	/*!< POR captured PIO status registers */
	__I  uint32_t  RESERVED15[18];
	__IO uint32_t  BODCTRL;			/*!< Brown Out Detect register */
	__IO uint32_t  SYSTCKCAL;		/*!< System tick counter calibration register */
#if defined(MCU_IS_LPC1315)
	__I  uint32_t  RESERVED16[6];
	__IO uint32_t  IRQLATENCY;		/*!< IRQ delay register */
	__IO uint32_t  NMISRC;			/*!< NMI source control register,some parts only */
	__IO uint32_t  PINTSEL[8];		/*!< GPIO pin interrupt select register 0-7 */
	__IO uint32_t  USBCLKCTRL;		/*!< USB clock control register, LPC134x only */
	__I  uint32_t  USBCLKST;		/*!< USB clock status register, LPC134x only */
	__I  uint32_t  RESERVED17[25];
	__IO uint32_t  STARTERP0;		/*!< Start logic 0 interrupt wake-up enable register */
	__I  uint32_t  RESERVED18[3];
	__IO uint32_t  STARTERP1;		/*!< Start logic 1 interrupt wake-up enable register */
	__I  uint32_t  RESERVED19[6];
#else
	__I  uint32_t  RESERVED16[42];
	LPC_SYSCTL_STARTST_T STARTLOGIC[2];
	__I  uint32_t  RESERVED17[4];
#endif
	__IO uint32_t  PDSLEEPCFG;		/*!< Power down states in deep sleep mode register */
	__IO uint32_t  PDWAKECFG;		/*!< Power down states in wake up from deep sleep register */
	__IO uint32_t  PDRUNCFG;		/*!< Power configuration register*/
	__I  uint32_t  RESERVED20[110];
	__I  uint32_t  DEVICEID;		/*!< Device ID register */
} LPC_SYSCON_TypeDef;


/*------------- Pin Connect Block (IOCON) --------------------------------*/
#ifdef MCU_IS_LPC1315

typedef struct {                            /*!< (@ 0x40044000) IOCONFIG Structure     */
  __IO uint32_t RESET_PIO0_0;               /*!< (@ 0x40044000) I/O configuration for pin RESET/PIO0_0 */
  __IO uint32_t PIO0_1;                     /*!< (@ 0x40044004) I/O configuration for pin PIO0_1/CLKOUT/CT32B0_MAT2/USB_FTOGGLE */
  __IO uint32_t PIO0_2;                     /*!< (@ 0x40044008) I/O configuration for pin PIO0_2/SSEL0/CT16B0_CAP0 */
  __IO uint32_t PIO0_3;                     /*!< (@ 0x4004400C) I/O configuration for pin PIO0_3/USB_VBUS */
  __IO uint32_t PIO0_4;                     /*!< (@ 0x40044010) I/O configuration for pin PIO0_4/SCL */
  __IO uint32_t PIO0_5;                     /*!< (@ 0x40044014) I/O configuration for pin PIO0_5/SDA */
  __IO uint32_t PIO0_6;                     /*!< (@ 0x40044018) I/O configuration for pin PIO0_6/USB_CONNECT/SCK0 */
  __IO uint32_t PIO0_7;                     /*!< (@ 0x4004401C) I/O configuration for pin PIO0_7/CTS */
  __IO uint32_t PIO0_8;                     /*!< (@ 0x40044020) I/O configuration for pin PIO0_8/MISO0/CT16B0_MAT0 */
  __IO uint32_t PIO0_9;                     /*!< (@ 0x40044024) I/O configuration for pin PIO0_9/MOSI0/CT16B0_MAT1 */
  __IO uint32_t SWCLK_PIO0_10;              /*!< (@ 0x40044028) I/O configuration for pin SWCLK/PIO0_10/ SCK0/CT16B0_MAT2 */
  __IO uint32_t TDI_PIO0_11;                /*!< (@ 0x4004402C) I/O configuration for pin TDI/PIO0_11/AD0/CT32B0_MAT3 */
  __IO uint32_t TMS_PIO0_12;                /*!< (@ 0x40044030) I/O configuration for pin TMS/PIO0_12/AD1/CT32B1_CAP0 */
  __IO uint32_t TDO_PIO0_13;                /*!< (@ 0x40044034) I/O configuration for pin TDO/PIO0_13/AD2/CT32B1_MAT0 */
  __IO uint32_t TRST_PIO0_14;               /*!< (@ 0x40044038) I/O configuration for pin TRST/PIO0_14/AD3/CT32B1_MAT1 */
  __IO uint32_t SWDIO_PIO0_15;              /*!< (@ 0x4004403C) I/O configuration for pin SWDIO/PIO0_15/AD4/CT32B1_MAT2 */
  __IO uint32_t PIO0_16;                    /*!< (@ 0x40044040) I/O configuration for pin PIO0_16/AD5/CT32B1_MAT3/ WAKEUP */
  __IO uint32_t PIO0_17;                    /*!< (@ 0x40044044) I/O configuration for pin PIO0_17/RTS/CT32B0_CAP0/SCLK */
  __IO uint32_t PIO0_18;                    /*!< (@ 0x40044048) I/O configuration for pin PIO0_18/RXD/CT32B0_MAT0 */
  __IO uint32_t PIO0_19;                    /*!< (@ 0x4004404C) I/O configuration for pin PIO0_19/TXD/CT32B0_MAT1 */
  __IO uint32_t PIO0_20;                    /*!< (@ 0x40044050) I/O configuration for pin PIO0_20/CT16B1_CAP0 */
  __IO uint32_t PIO0_21;                    /*!< (@ 0x40044054) I/O configuration for pin PIO0_21/CT16B1_MAT0/MOSI1 */
  __IO uint32_t PIO0_22;                    /*!< (@ 0x40044058) I/O configuration for pin PIO0_22/AD6/CT16B1_MAT1/MISO1 */
  __IO uint32_t PIO0_23;                    /*!< (@ 0x4004405C) I/O configuration for pin PIO0_23/AD7 */
  __IO uint32_t PIO1_0;                 /*!< Offset: 0x060 */
  __IO uint32_t PIO1_1;         
  __IO uint32_t PIO1_2;       
  __IO uint32_t PIO1_3;      
  __IO uint32_t PIO1_4;                 /*!< Offset: 0x070 */
  __IO uint32_t PIO1_5;                     /*!< (@ 0x40044074) I/O configuration for pin PIO1_5/CT32B1_CAP1 */
  __IO uint32_t PIO1_6;     
  __IO uint32_t PIO1_7;       
  __IO uint32_t PIO1_8;                 /*!< Offset: 0x080 */
  __IO uint32_t PIO1_9;        
  __IO uint32_t PIO1_10;        
  __IO uint32_t PIO1_11;       
  __IO uint32_t PIO1_12;                /*!< Offset: 0x090 */
  __IO uint32_t PIO1_13;                    /*!< (@ 0x40044094) I/O configuration for pin PIO1_13/DTR/CT16B0_MAT0/TXD */
  __IO uint32_t PIO1_14;                    /*!< (@ 0x40044098) I/O configuration for pin PIO1_14/DSR/CT16B0_MAT1/RXD */
  __IO uint32_t PIO1_15;                    /*!< (@ 0x4004409C) I/O configuration for pin PIO1_15/DCD/ CT16B0_MAT2/SCK1 */
  __IO uint32_t PIO1_16;                    /*!< (@ 0x400440A0) I/O configuration for pin PIO1_16/RI/CT16B0_CAP0 */
  __IO uint32_t PIO1_17;
  __IO uint32_t PIO1_18;
  __IO uint32_t PIO1_19;                    /*!< (@ 0x400440AC) I/O configuration for pin PIO1_19/DTR/SSEL1 */
  __IO uint32_t PIO1_20;                    /*!< (@ 0x400440B0) I/O configuration for pin PIO1_20/DSR/SCK1 */
  __IO uint32_t PIO1_21;                    /*!< (@ 0x400440B4) I/O configuration for pin PIO1_21/DCD/MISO1 */
  __IO uint32_t PIO1_22;                    /*!< (@ 0x400440B8) I/O configuration for pin PIO1_22/RI/MOSI1 */
  __IO uint32_t PIO1_23;                    /*!< (@ 0x400440BC) I/O configuration for pin PIO1_23/CT16B1_MAT1/SSEL1 */
  __IO uint32_t PIO1_24;                    /*!< (@ 0x400440C0) I/O configuration for pin PIO1_24/ CT32B0_MAT0 */
  __IO uint32_t PIO1_25;                    /*!< (@ 0x400440C4) I/O configuration for pin PIO1_25/CT32B0_MAT1 */
  __IO uint32_t PIO1_26;                    /*!< (@ 0x400440C8) I/O configuration for pin PIO1_26/CT32B0_MAT2/ RXD */
  __IO uint32_t PIO1_27;                    /*!< (@ 0x400440CC) I/O configuration for pin PIO1_27/CT32B0_MAT3/ TXD */
  __IO uint32_t PIO1_28;                    /*!< (@ 0x400440D0) I/O configuration for pin PIO1_28/CT32B0_CAP0/ SCLK */
  __IO uint32_t PIO1_29;                    /*!< (@ 0x400440D4) I/O configuration for pin PIO1_29/SCK0/ CT32B0_CAP1 */
  __IO uint32_t PIO1_30;
  __IO uint32_t PIO1_31;                    /*!< (@ 0x400440DC) I/O configuration for pin PIO1_31 */
} LPC_IOCON_TypeDef;

#else 

typedef struct
{
  __IO uint32_t PIO2_6;
       uint32_t RESERVED0[1];
  __IO uint32_t PIO2_0;
  __IO uint32_t RESET_PIO0_0;
  __IO uint32_t PIO0_1;
  __IO uint32_t PIO1_8;
       uint32_t RESERVED1[1];
  __IO uint32_t PIO0_2;

  __IO uint32_t PIO2_7;
  __IO uint32_t PIO2_8;
  __IO uint32_t PIO2_1;
  __IO uint32_t PIO0_3;
  __IO uint32_t PIO0_4;
  __IO uint32_t PIO0_5;
  __IO uint32_t PIO1_9;
  __IO uint32_t PIO3_4;

  __IO uint32_t PIO2_4;
  __IO uint32_t PIO2_5;
  __IO uint32_t PIO3_5;
  __IO uint32_t PIO0_6;
  __IO uint32_t PIO0_7;
  __IO uint32_t PIO2_9;
  __IO uint32_t PIO2_10;
  __IO uint32_t PIO2_2;

  __IO uint32_t PIO0_8;
  __IO uint32_t PIO0_9;
  union {
	  // SWCLK_PIO0_10 preferred name rather than original JTAG_TCK_PIO0_10
	  __IO uint32_t SWCLK_PIO0_10;
	  __IO uint32_t JTAG_TCK_PIO0_10;
  };
  __IO uint32_t PIO1_10;
  __IO uint32_t PIO2_11;
  union {
	  // R_PIO0_11 preferred name rather than original JTAG_TDI_PIO0_11
	  __IO uint32_t R_PIO0_11;
	  __IO uint32_t JTAG_TDI_PIO0_11;
  };
  union {
	  // R_PIO1_0 preferred name rather than original JTAG_TMS_PIO1_0
	  __IO uint32_t R_PIO1_0;
	  __IO uint32_t JTAG_TMS_PIO1_0;
  };
  union {
	  // R_PIO1_1 preferred name rather than original JTAG_TDO_PIO1_1
	  __IO uint32_t R_PIO1_1;
	  __IO uint32_t JTAG_TDO_PIO1_1;
  };

  union {
	  // R_PIO1_2 preferred name rather than original JTAG_nTRST_PIO1_2
	  __IO uint32_t R_PIO1_2;
	  __IO uint32_t JTAG_nTRST_PIO1_2;
  };
  __IO uint32_t PIO3_0;
  __IO uint32_t PIO3_1;
  __IO uint32_t PIO2_3;
  union {
	  // SWDIO_PIO1_3 preferred name rather than original ARM_SWDIO_PIO1_3
	  __IO uint32_t SWDIO_PIO1_3;
	  __IO uint32_t ARM_SWDIO_PIO1_3;
  };

  __IO uint32_t PIO1_4;
  __IO uint32_t PIO1_11;
  __IO uint32_t PIO3_2;

  __IO uint32_t PIO1_5;
  __IO uint32_t PIO1_6;
  __IO uint32_t PIO1_7;
  __IO uint32_t PIO3_3;
  union {
	  // SCK_LOC preferred name rather than original SCKLOC
	  __IO uint32_t SCK_LOC;                /*!< Offset: 0x0B0 SCK pin location select Register (R/W) */
	  __IO uint32_t SCKLOC;
  };
  __IO uint32_t DSR_LOC;                /*!< Offset: 0x0B4 DSR pin location select Register (R/W) */
  __IO uint32_t DCD_LOC;                /*!< Offset: 0x0B8 DCD pin location select Register (R/W) */
  __IO uint32_t RI_LOC;                 /*!< Offset: 0x0BC RI pin location Register (R/W) */
} LPC_IOCON_TypeDef;

#endif

/*------------- Power Management Unit (PMU) --------------------------*/
typedef struct
{
  __IO uint32_t PCON;
  __IO uint32_t GPREG0;
  __IO uint32_t GPREG1;
  __IO uint32_t GPREG2;
  __IO uint32_t GPREG3;
  __IO uint32_t GPREG4;
} LPC_PMU_TypeDef;


/*------------- General Purpose Input/Output (GPIO) --------------------------*/

#ifdef MCU_IS_LPC1315

typedef struct {                            
  union {
    struct {
      __IO uint8_t B0[32];                       /*!< (@ 0x50000000) Byte pin registers port 0; pins PIO0_0 to PIO0_31 */
      __IO uint8_t B1[32];                       /*!< (@ 0x50000020) Byte pin registers port 1 */
    };
    __IO uint8_t B[64];                       /*!< (@ 0x50000000) Byte pin registers port 0/1 */
  };
  __I  uint32_t RESERVED0[1008];
  union {
    struct {
      __IO uint32_t W0[32];                      /*!< (@ 0x50001000) Word pin registers port 0 */
      __IO uint32_t W1[32];                      /*!< (@ 0x50001080) Word pin registers port 1 */
    };
    __IO uint32_t W[64];                       /*!< (@ 0x50001000) Word pin registers port 0/1 */
  };
       uint32_t RESERVED1[960];
  __IO uint32_t DIR[2];			/* 0x2000 */
       uint32_t RESERVED2[30];
  __IO uint32_t MASK[2];		/* 0x2080 */
       uint32_t RESERVED3[30];
  __IO uint32_t PIN[2];			/* 0x2100 */
       uint32_t RESERVED4[30];
  __IO uint32_t MPIN[2];		/* 0x2180 */
       uint32_t RESERVED5[30];
  __IO uint32_t SET[2];			/* 0x2200 */
       uint32_t RESERVED6[30];
  __O  uint32_t CLR[2];			/* 0x2280 */
       uint32_t RESERVED7[30];
  __O  uint32_t NOT[2];			/* 0x2300 */
} LPC_GPIO_TypeDef;

// GPIO pin interrupt register block structure
typedef struct {				/*!< GPIO_PIN_INT Structure */
	__IO uint32_t  ISEL;		/*!< Pin Interrupt Mode register */
	__IO uint32_t  IENR;		/*!< Pin Interrupt Enable (Rising) register */
	__O  uint32_t  SIENR;		/*!< Set Pin Interrupt Enable (Rising) register */
	__O  uint32_t  CIENR;		/*!< Clear Pin Interrupt Enable (Rising) register */
	__IO uint32_t  IENF;		/*!< Pin Interrupt Enable Falling Edge / Active Level register */
	__O  uint32_t  SIENF;		/*!< Set Pin Interrupt Enable Falling Edge / Active Level register */
	__O  uint32_t  CIENF;		/*!< Clear Pin Interrupt Enable Falling Edge / Active Level address */
	__IO uint32_t  RISE;		/*!< Pin Interrupt Rising Edge register */
	__IO uint32_t  FALL;		/*!< Pin Interrupt Falling Edge register */
	__IO uint32_t  IST;			/*!< Pin Interrupt Status register */
} LPC_GPIOINT_Typedef;

// GPIO grouped interrupt register block structure
typedef struct {					/*!< GPIO_GROUP_INTn Structure */
	__IO uint32_t  CTRL;			/*!< GPIO grouped interrupt control register */
	__I  uint32_t  RESERVED0[7];
	__IO uint32_t  PORT_POL[8];		/*!< GPIO grouped interrupt port polarity register */
	__IO uint32_t  PORT_ENA[8];		/*!< GPIO grouped interrupt port m enable register */
} LPC_GPIOGROUPINT_Typedef;

#else // MCU_IS_LPC1315

typedef struct
{
  union {
    __IO uint32_t MASKED_ACCESS[4096];
    struct {
         uint32_t RESERVED0[4095];
    __IO uint32_t DATA;
    };
  };
       uint32_t RESERVED1[4096];
  __IO uint32_t DIR;
  __IO uint32_t IS;
  __IO uint32_t IBE;
  __IO uint32_t IEV;
  __IO uint32_t IE;
  __IO uint32_t RIS;
  __IO uint32_t MIS;
  __IO uint32_t IC;
} LPC_GPIO_TypeDef;

#endif //MCU_IS_LPC1315

/*------------- Timer (TMR) --------------------------------------------------*/
typedef struct
{
  __IO uint32_t IR;
  __IO uint32_t TCR;
  __IO uint32_t TC;
  __IO uint32_t PR;
  __IO uint32_t PC;
  __IO uint32_t MCR;
  __IO uint32_t MR0;
  __IO uint32_t MR1;
  __IO uint32_t MR2;
  __IO uint32_t MR3;
  __IO uint32_t CCR;
  __I  uint32_t CR0;
       uint32_t RESERVED1[3];
  __IO uint32_t EMR;
       uint32_t RESERVED2[12];
  __IO uint32_t CTCR;
  __IO uint32_t PWMC;
} LPC_TMR_TypeDef;

/*------------- Universal Asynchronous Receiver Transmitter (UART) -----------*/
typedef struct
{
  union {
  __I  uint32_t  RBR;
  __O  uint32_t  THR;
  __IO uint32_t  DLL;
  };
  union {
  __IO uint32_t  DLM;
  __IO uint32_t  IER;
  };
  union {
  __I  uint32_t  IIR;
  __O  uint32_t  FCR;
  };
  __IO uint32_t  LCR;
  __IO uint32_t  MCR;
  __I  uint32_t  LSR;
  __I  uint32_t  MSR;
  __IO uint32_t  SCR;
  __IO uint32_t  ACR;
  __IO uint32_t  ICR;
  __IO uint32_t  FDR;
       uint32_t  RESERVED0;
  __IO uint32_t  TER;
       uint32_t  RESERVED1[6];
  __IO uint32_t  RS485CTRL;
  __IO uint32_t  ADRMATCH;
  __IO uint32_t  RS485DLY;
  __I  uint32_t  FIFOLVL;
} LPC_UART_TypeDef;

/*------------- Synchronous Serial Communication (SSP) -----------------------*/
typedef struct
{
  __IO uint32_t CR0;
  __IO uint32_t CR1;
  __IO uint32_t DR;
  __I  uint32_t SR;
  __IO uint32_t CPSR;
  __IO uint32_t IMSC;
  __IO uint32_t RIS;
  __IO uint32_t MIS;
  __IO uint32_t ICR;
} LPC_SSP_TypeDef;

/*------------- Inter-Integrated Circuit (I2C) -------------------------------*/
typedef struct
{
  __IO uint32_t CONSET;
  __I  uint32_t STAT;
  __IO uint32_t DAT;
  __IO uint32_t ADR0;
  __IO uint32_t SCLH;
  __IO uint32_t SCLL;
  __O  uint32_t CONCLR;
  __IO uint32_t MMCTRL;
  __IO uint32_t ADR1;
  __IO uint32_t ADR2;
  __IO uint32_t ADR3;
  __I  uint32_t DATA_BUFFER;
  __IO uint32_t MASK0;
  __IO uint32_t MASK1;
  __IO uint32_t MASK2;
  __IO uint32_t MASK3;
} LPC_I2C_TypeDef;

/*------------- Watchdog Timer (WDT) -----------------------------------------*/
typedef struct
{
  __IO uint32_t MOD;
  __IO uint32_t TC;
  __O  uint32_t FEED;
  __I  uint32_t TV;
  uint32_t RESERVED0;
__IO uint32_t WARNINT;				/*!< Offset: 0x014 Watchdog timer warning int. register (R/W) */
__IO uint32_t WINDOW;				/*!< Offset: 0x018 Watchdog timer window value register (R/W) */

} LPC_WDT_TypeDef;

/*------------- Analog-to-Digital Converter (ADC) ----------------------------*/
typedef struct
{
  __IO uint32_t CR;
  __IO uint32_t GDR;
       uint32_t RESERVED0;
  __IO uint32_t INTEN;
  union {
	  __IO uint32_t DR[8];
	  struct {
	  __I  uint32_t DR0;
	  __I  uint32_t DR1;
	  __I  uint32_t DR2;
	  __I  uint32_t DR3;
	  __I  uint32_t DR4;
	  __I  uint32_t DR5;
	  __I  uint32_t DR6;
	  __I  uint32_t DR7;
	  };
  };
	  __I  uint32_t STAT;
} LPC_ADC_TypeDef;


/*------------- Universal Serial Bus (USB) -----------------------------------*/
typedef struct
{
  __I  uint32_t DevIntSt;            /* USB Device Interrupt Registers     */
  __IO uint32_t DevIntEn;
  __O  uint32_t DevIntClr;
  __O  uint32_t DevIntSet;

  __O  uint32_t CmdCode;             /* USB Device SIE Command Registers   */
  __I  uint32_t CmdData;

  __I  uint32_t RxData;              /* USB Device Transfer Registers      */
  __O  uint32_t TxData;
  __I  uint32_t RxPLen;
  __O  uint32_t TxPLen;
  __IO uint32_t Ctrl;
  __O  uint32_t DevFIQSel;
} LPC_USB_TypeDef;

#if defined ( __CC_ARM   )
#pragma no_anon_unions
#endif


/******************************************************************************/
/*                         Peripheral memory map                              */
/******************************************************************************/
/* Base addresses                                                             */
#define LPC_FLASH_BASE        (0x00000000UL)
#define LPC_RAM_BASE          (0x10000000UL)
#define LPC_APB0_BASE         (0x40000000UL)
#define LPC_AHB_BASE          (0x50000000UL)

/* APB0 peripherals                                                           */
#define LPC_I2C_BASE          (LPC_APB0_BASE + 0x00000)
#define LPC_WDT_BASE          (LPC_APB0_BASE + 0x04000)
#define LPC_UART_BASE         (LPC_APB0_BASE + 0x08000)
#define LPC_CT16B0_BASE       (LPC_APB0_BASE + 0x0C000)
#define LPC_CT16B1_BASE       (LPC_APB0_BASE + 0x10000)
#define LPC_CT32B0_BASE       (LPC_APB0_BASE + 0x14000)
#define LPC_CT32B1_BASE       (LPC_APB0_BASE + 0x18000)
#define LPC_ADC_BASE          (LPC_APB0_BASE + 0x1C000)

#ifdef MCU_IS_LPC1315
#       define LPC_USB_BASE          (LPC_APB0_BASE + 0x80000)
#else
#       define LPC_USB_BASE          (LPC_APB0_BASE + 0x20000)
#endif

#define LPC_PMU_BASE          (LPC_APB0_BASE + 0x38000)
// LPC_SSP_BASE original name, LPC_SSP0_BASE new preferred name
#define LPC_SSP_BASE          (LPC_APB0_BASE + 0x40000)
#define LPC_SSP0_BASE         (LPC_APB0_BASE + 0x40000)
#define LPC_IOCON_BASE        (LPC_APB0_BASE + 0x44000)
#define LPC_SYSCON_BASE       (LPC_APB0_BASE + 0x48000)
#define LPC_SSP1_BASE         (LPC_APB0_BASE + 0x58000)

/* AHB peripherals                                                            */	
#define LPC_GPIO_BASE         (LPC_AHB_BASE  + 0x00000)
#define LPC_GPIO0_BASE        (LPC_AHB_BASE  + 0x00000)

#ifdef MCU_IS_LPC1311
#       define LPC_GPIO1_BASE        (LPC_AHB_BASE  + 0x10000)
#       define LPC_GPIO2_BASE        (LPC_AHB_BASE  + 0x20000)
#       define LPC_GPIO3_BASE        (LPC_AHB_BASE  + 0x30000)
#endif

/******************************************************************************/
/*                         Peripheral declaration                             */
/******************************************************************************/
#define LPC_I2C               ((LPC_I2C_TypeDef    *) LPC_I2C_BASE   )
#define LPC_WDT               ((LPC_WDT_TypeDef    *) LPC_WDT_BASE   )
#define LPC_UART              ((LPC_UART_TypeDef   *) LPC_UART_BASE  )
#define LPC_TMR16B0           ((LPC_TMR_TypeDef    *) LPC_CT16B0_BASE)
#define LPC_TMR16B1           ((LPC_TMR_TypeDef    *) LPC_CT16B1_BASE)
#define LPC_TMR32B0           ((LPC_TMR_TypeDef    *) LPC_CT32B0_BASE)
#define LPC_TMR32B1           ((LPC_TMR_TypeDef    *) LPC_CT32B1_BASE)
#define LPC_ADC               ((LPC_ADC_TypeDef    *) LPC_ADC_BASE   )
#define LPC_PMU               ((LPC_PMU_TypeDef    *) LPC_PMU_BASE   )
// LPC_SSP original name, LPC_SSP0 new preferred name
#define LPC_SSP               ((LPC_SSP_TypeDef    *) LPC_SSP_BASE   )
#define LPC_SSP0              ((LPC_SSP_TypeDef    *) LPC_SSP0_BASE  )
#define LPC_SSP1              ((LPC_SSP_TypeDef    *) LPC_SSP1_BASE  )
#define LPC_IOCON             ((LPC_IOCON_TypeDef  *) LPC_IOCON_BASE )
#define LPC_SYSCON            ((LPC_SYSCON_TypeDef *) LPC_SYSCON_BASE)
#define LPC_USB               ((LPC_USB_TypeDef    *) LPC_USB_BASE   )

#ifdef MCU_IS_LPC1315
#       define LPC_GPIO_PIN_INT_BASE     0x4004C000
#       define LPC_GPIO_GROUP_INT0_BASE  0x4005C000
#       define LPC_GPIO_GROUP_INT1_BASE  0x40060000

#       define LPC_GPIO       ((LPC_GPIO_TypeDef    *) LPC_GPIO0_BASE )
#       define LPC_GPIO0        LPC_GPIO
#       define LPC_GPIO1        LPC_GPIO

#       define LPC_GPIO_PIN_INT          ((LPC_GPIOINT_Typedef       *) LPC_GPIO_PIN_INT_BASE)
#       define LPC_GPIO_GROUP_INT0       ((LPC_GPIOGROUPINT_Typedef     *) LPC_GPIO_GROUP_INT0_BASE)
#       define LPC_GPIO_GROUP_INT1       ((LPC_GPIOGROUPINT_Typedef     *) LPC_GPIO_GROUP_INT1_BASE)
#else
#       define LPC_GPIO0             ((LPC_GPIO_TypeDef   *) LPC_GPIO0_BASE )
#       define LPC_GPIO1             ((LPC_GPIO_TypeDef   *) LPC_GPIO1_BASE )
#       define LPC_GPIO2             ((LPC_GPIO_TypeDef   *) LPC_GPIO2_BASE )
#       define LPC_GPIO3             ((LPC_GPIO_TypeDef   *) LPC_GPIO3_BASE )
#endif



/******************************************************************************/
/*                         Alias for Libs-hardware                            */
/******************************************************************************/

#define UART0_IRQn              UART_IRQn
#define LPC_UART0_BASE          LPC_UART_BASE
#define LPC_UART0               LPC_UART

#define LPC_I2C0                LPC_I2C



#endif  // __LPC13xx_H__
