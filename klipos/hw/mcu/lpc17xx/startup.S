/*****************************************************************************/
/* startup_LPC17xx.s: Startup file for LPC17xx device series                 */
/*****************************************************************************/
/* Version: CodeSourcery Sourcery G++ Lite (with CS3)                        */
/*****************************************************************************/

/* mthomas:
   - replaced CM3 _start with data-copy, bss-init
   - added syntax unified
   - moved NMI to UsageFault handlers in reset section to minimize checksum
     modifications

  baptiste:
  - remove jtag startup

*/

/*
//*** <<< Use Configuration Wizard in Context Menu >>> ***
*/


/*
// <h> Stack Configuration
//   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
// </h>
*/

.syntax unified

    .equ    Stack_Size, Kernel_Stack_Size
    .section ".stack", "w"
    .align  3
    .globl  __cs3_stack_mem
    .globl  __cs3_stack_size
__cs3_stack_mem:
    .if     Stack_Size
    .space  Stack_Size
    .endif
    .size   __cs3_stack_mem,  . - __cs3_stack_mem
    .set    __cs3_stack_size, . - __cs3_stack_mem


/* remove heap section baptiste 08.08.2011

    .equ    Heap_Size,  0x00001000

    .section ".heap", "w"
    .align  3
    .globl  __cs3_heap_start
    .globl  __cs3_heap_end
__cs3_heap_start:
    .if     Heap_Size
    .space  Heap_Size
    .endif
__cs3_heap_end:
*/

/* Vector Table */

    .section ".cs3.interrupt_vector"
    .globl  __cs3_interrupt_vector_cortex_m
    .type   __cs3_interrupt_vector_cortex_m, %object

__cs3_interrupt_vector_cortex_m:
      __cs3_stack                 /* Top of Stack                 */
      __cs3_reset                 /* Reset Handler                */
      NMI_Handler                 /* NMI Handler                  */
      HardFault_Handler           /* Hard Fault Handler           */
      MemManage_Handler           /* MPU Fault Handler            */
      BusFault_Handler            /* Bus Fault Handler            */
      UsageFault_Handler          /* Usage Fault Handler          */
      0xefff9cda /*0xefff79be                  /* Checksum, see LPC1xxx manual */
      0                           /* Reserved                     */
      0                           /* Reserved                     */
      0                           /* Reserved                     */
      SVC_Handler                 /* SVCall Handler               */
      DebugMon_Handler            /* Debug Monitor Handler        */
      0                           /* Reserved                     */
      PendSV_Handler              /* PendSV Handler               */
      SysTick_Handler             /* SysTick Handler              */

    /* External Interrupts */
      WDT_IRQHandler              /* 16: Watchdog Timer               */
      TIMER0_IRQHandler           /* 17: Timer0                       */
      TIMER1_IRQHandler           /* 18: Timer1                       */
      TIMER2_IRQHandler           /* 19: Timer2                       */
      TIMER3_IRQHandler           /* 20: Timer3                       */
      UART0_IRQHandler            /* 21: UART0                        */
      UART1_IRQHandler            /* 22: UART1                        */
      UART2_IRQHandler            /* 23: UART2                        */
      UART3_IRQHandler            /* 24: UART3                        */
      PWM1_IRQHandler             /* 25: PWM1                         */
      I2C0_IRQHandler             /* 26: I2C0                         */
      I2C1_IRQHandler             /* 27: I2C1                         */
      I2C2_IRQHandler             /* 28: I2C2                         */
      SPI_IRQHandler              /* 29: SPI                          */
      SSP0_IRQHandler             /* 30: SSP0                         */
      SSP1_IRQHandler             /* 31: SSP1                         */
      PLL0_IRQHandler             /* 32: PLL0 Lock (Main PLL)         */
      RTC_IRQHandler              /* 33: Real Time Clock              */
      EINT0_IRQHandler            /* 34: External Interrupt 0         */
      EINT1_IRQHandler            /* 35: External Interrupt 1         */
      EINT2_IRQHandler            /* 36: External Interrupt 2         */
      EINT3_IRQHandler            /* 37: External Interrupt 3         */
      ADC_IRQHandler              /* 38: A/D Converter                */
      BOD_IRQHandler              /* 39: Brown-Out Detect             */
      USB_IRQHandler              /* 40: USB                          */
      CAN_IRQHandler              /* 41: CAN                          */
      DMA_IRQHandler              /* 42: General Purpose DMA          */
      I2S_IRQHandler              /* 43: I2S                          */
      ENET_IRQHandler             /* 44: Ethernet                     */
      RIT_IRQHandler              /* 45: Repetitive Interrupt Timer   */
      MCPWM_IRQHandler            /* 46: Motor Control PWM            */
      QEI_IRQHandler              /* 47: Quadrature Encoder Interface */
      PLL1_IRQHandler             /* 48: PLL1 Lock (USB PLL)          */

    .size   __cs3_interrupt_vector_cortex_m, . - __cs3_interrupt_vector_cortex_m


    .thumb


/* Reset Handler */

    .section .cs3.reset,"x",%progbits
    .thumb_func
    .globl  __cs3_reset_cortex_m
    .type   __cs3_reset_cortex_m, %function
__cs3_reset_cortex_m:
    .fnstart

/* delay at startup to let JTAG-connection catch-up */
/*	baptiste 2010.11.21 remove next code... 
	LDR R0, =startup_delay
	BLX R0
*/

/* Copy the data segment initializers from flash to SRAM */
.extern _etext
.extern _sdata
.extern _edata
    ldr   r1, =_etext
    ldr   r2, =_sdata
    ldr   r3, =_edata
1:  cmp   r2, r3
    ittt  lo
    ldrlo r0, [r1], #4
    strlo r0, [r2], #4
    blo   1b

/* Zero fill the bss segment. */
.extern _sbss
.extern _ebss
    movs  r0, #0
    ldr   r1, =_sbss
    ldr   r2, =_ebss
2:  cmp   r1, r2
    itt   lo
    strlo r0, [r1], #4
    blo   2b

/* call __libc_init_array - needed for C++ support */
/*    LDR     R0, =__libc_init_array */
/*    BLX     R0 */

/* call system init in libs-hardware pob-technology */
 /*   LDR     R0,=InitLowLevelCpu
    BLX     R0
*/
    BL      initLowLevelCpu

/* call main() */
    LDR     R0,=main
    BX      R0

    B .

    .pool
    .cantunwind
    .fnend
    .size   __cs3_reset_cortex_m,.-__cs3_reset_cortex_m

/* Exception Handlers */

    .weak   NMI_Handler
    .type   NMI_Handler, %function
NMI_Handler:
    B       .
    .size   NMI_Handler, . - NMI_Handler

    .weak   HardFault_Handler
    .type   HardFault_Handler, %function
HardFault_Handler:
    B       .
    .size   HardFault_Handler, . - HardFault_Handler

    .weak   MemManage_Handler
    .type   MemManage_Handler, %function
MemManage_Handler:
    B       .
    .size   MemManage_Handler, . - MemManage_Handler

    .weak   BusFault_Handler
    .type   BusFault_Handler, %function
BusFault_Handler:
    B       .
    .size   BusFault_Handler, . - BusFault_Handler

    .weak   UsageFault_Handler
    .type   UsageFault_Handler, %function
UsageFault_Handler:
    B       .
    .size   UsageFault_Handler, . - UsageFault_Handler




    .section ".text"

    .weak   SVC_Handler
    .type   SVC_Handler, %function
SVC_Handler:
    B       .
    .size   SVC_Handler, . - SVC_Handler

    .weak   DebugMon_Handler
    .type   DebugMon_Handler, %function
DebugMon_Handler:
    B       .
    .size   DebugMon_Handler, . - DebugMon_Handler

    .weak   PendSV_Handler
    .type   PendSV_Handler, %function
PendSV_Handler:
    B       .
    .size   PendSV_Handler, . - PendSV_Handler

    .weak   SysTick_Handler
    .type   SysTick_Handler, %function
SysTick_Handler:
    B       .
    .size   SysTick_Handler, . - SysTick_Handler


/* IRQ Handlers */

    .globl  Default_Handler
    .type   Default_Handler, %function
Default_Handler:
    B       .
    .size   Default_Handler, . - Default_Handler

    .macro  IRQ handler
/* weak : ca dit que le code est peut etre defini plus tard ailleurs (ou pas) */
    .weak   \handler
    .set    \handler, Default_Handler
    .endm

    IRQ     WDT_IRQHandler
    IRQ     TIMER0_IRQHandler
    IRQ     TIMER1_IRQHandler
    IRQ     TIMER2_IRQHandler
    IRQ     TIMER3_IRQHandler
    IRQ     UART0_IRQHandler
    IRQ     UART1_IRQHandler
    IRQ     UART2_IRQHandler
    IRQ     UART3_IRQHandler
    IRQ     PWM1_IRQHandler
    IRQ     I2C0_IRQHandler
    IRQ     I2C1_IRQHandler
    IRQ     I2C2_IRQHandler
    IRQ     SPI_IRQHandler
    IRQ     SSP0_IRQHandler
    IRQ     SSP1_IRQHandler
    IRQ     PLL0_IRQHandler
    IRQ     RTC_IRQHandler
    IRQ     EINT0_IRQHandler
    IRQ     EINT1_IRQHandler
    IRQ     EINT2_IRQHandler
    IRQ     EINT3_IRQHandler
    IRQ     ADC_IRQHandler
    IRQ     BOD_IRQHandler
    IRQ     USB_IRQHandler
    IRQ     CAN_IRQHandler
    IRQ     DMA_IRQHandler
    IRQ     I2S_IRQHandler
    IRQ     ENET_IRQHandler
    IRQ     RIT_IRQHandler
    IRQ     MCPWM_IRQHandler
    IRQ     QEI_IRQHandler
    IRQ     PLL1_IRQHandler

    .end
