/* startup code for cortex-m3 lpc13xx */


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
    .long   __cs3_stack                 /* Top of Stack                 */
    .long   __cs3_reset                 /* Reset Handler                */
    .long   NMI_Handler                 /* NMI Handler                  */
    .long   HardFault_Handler           /* Hard Fault Handler           */
    .long   MemManage_Handler           /* MPU Fault Handler            */
    .long   BusFault_Handler            /* Bus Fault Handler            */
    .long   UsageFault_Handler          /* Usage Fault Handler          */
    .long   0                           /* Checksum, see LPC1xxx manual */
    .long   0                           /* Reserved                     */
    .long   0                           /* Reserved                     */
    .long   0                           /* Reserved                     */
    .long   SVC_Handler                 /* SVCall Handler               */
    .long   DebugMon_Handler            /* Debug Monitor Handler        */
    .long   0                           /* Reserved                     */
    .long   PendSV_Handler              /* PendSV Handler               */
    .long   SysTick_Handler             /* SysTick Handler              */

    /* External Interrupts */
    .if McuLpc1315 == 0
    .long WAKEUP_IRQn_Handler                          /*!< All I/O pins can be used as wakeup source.       */
    .long WAKEUP_IRQn_Handler                          /*!< There are 40 pins in total for LPC17xx           */
    .long WAKEUP_IRQn_Handler                  
    .long WAKEUP_IRQn_Handler                  
    .long WAKEUP_IRQn_Handler                     
    .long WAKEUP_IRQn_Handler                          
    .long WAKEUP_IRQn_Handler                          
    .long WAKEUP_IRQn_Handler                          
    .long WAKEUP_IRQn_Handler                          
    .long WAKEUP_IRQn_Handler                          
    .long WAKEUP_IRQn_Handler                        
    .long WAKEUP_IRQn_Handler                        
    .long WAKEUP_IRQn_Handler                        
    .long WAKEUP_IRQn_Handler                        
    .long WAKEUP_IRQn_Handler                        
    .long WAKEUP_IRQn_Handler                        
    .long WAKEUP_IRQn_Handler                        
    .long WAKEUP_IRQn_Handler                        
    .long WAKEUP_IRQn_Handler                        
    .long WAKEUP_IRQn_Handler                        
    .long WAKEUP_IRQn_Handler                        
    .long WAKEUP_IRQn_Handler                        
    .long WAKEUP_IRQn_Handler                        
    .long WAKEUP_IRQn_Handler                        
    .long WAKEUP_IRQn_Handler                        
    .long WAKEUP_IRQn_Handler                        
    .long WAKEUP_IRQn_Handler                        
    .long WAKEUP_IRQn_Handler                        
    .long WAKEUP_IRQn_Handler                        
    .long WAKEUP_IRQn_Handler                        
    .long WAKEUP_IRQn_Handler                        
    .long WAKEUP_IRQn_Handler                        
    .long WAKEUP_IRQn_Handler                        
    .long WAKEUP_IRQn_Handler                        
    .long WAKEUP_IRQn_Handler                        
    .long WAKEUP_IRQn_Handler                        
    .long WAKEUP_IRQn_Handler                        
    .long WAKEUP_IRQn_Handler                        
    .long WAKEUP_IRQn_Handler                        
    .long WAKEUP_IRQn_Handler                        
    .long I2C_IRQn_Handler                             /*!< I2C Interrupt                                    */
    .long TIMER_16_0_IRQn_Handler                      /*!< 16-bit Timer0 Interrupt                          */
    .long TIMER_16_1_IRQn_Handler                      /*!< 16-bit Timer1 Interrupt                          */
    .long TIMER_32_0_IRQn_Handler                      /*!< 32-bit Timer0 Interrupt                          */
    .long TIMER_32_1_IRQn_Handler                      /*!< 32-bit Timer1 Interrupt                          */
    .long SSP0_IRQn_Handler                            /*!< SSP0 Interrupt  - new name                                   */
    .long UART0_IRQHandler                             /*!< UART Interrupt                                   */
    .long USB_IRQn_Handler                             /*!< USB Regular Interrupt                            */
    .long USB_FIQn                                     /*!< USB Fast Interrupt                               */
    .long ADC_IRQn_Handler                             /*!< A/D Converter Interrupt                          */
    .long WDT_IRQn_Handler                             /*!< Watchdog timer Interrupt                         */  
    .long BOD_IRQn_Handler                             /*!< Brown Out Detect(BOD) Interrupt                  */
    .long RESERVED_IRQn_Handler                        /*!< Reserved Interrupt                               */
    .long EINT3_IRQn_Handler                           /*!< External Interrupt 3 Interrupt                   */
    .long EINT2_IRQn_Handler                           /*!< External Interrupt 2 Interrupt                   */
    .long EINT1_IRQn_Handler                           /*!< External Interrupt 1 Interrupt                   */
    .long EINT0_IRQn_Handler                           /*!< External Interrupt 0 Interrupt                   */
    .endif

    .if McuLpc1315 == 1
    .long PIN_INT0_IRQHandler                          /*!< GPIO Interrupt 0 Interrupt                       */
    .long PIN_INT1_IRQHandler                          /*!< GPIO Interrupt 1 Interrupt                       */
    .long PIN_INT2_IRQHandler                          /*!< GPIO Interrupt 2 Interrupt                       */
    .long PIN_INT3_IRQHandler                          /*!< GPIO Interrupt 3 Interrupt                       */
    .long PIN_INT4_IRQHandler                          /*!< GPIO Interrupt 4 Interrupt                       */
    .long PIN_INT5_IRQHandler                          /*!< GPIO Interrupt 5 Interrupt                       */
    .long PIN_INT6_IRQHandler                          /*!< GPIO Interrupt 6 Interrupt                       */
    .long PIN_INT7_IRQHandler                          /*!< GPIO Interrupt 7 Interrupt                       */
    .long GINT0_IRQHandler                             /*!< GPIO Group 0 Interrupt                           */
    .long GINT1_IRQHandler                             /*!< GPIO Group 1 Interrupt                           */
    .long RESERVED_IRQn_Handler                        /*!< Reserved Interrupt                               */
    .long RESERVED_IRQn_Handler                        /*!< Reserved Interrupt                               */
    .long RESERVED_IRQn_Handler                        /*!< RIT Interrupt                                    */
    .long RESERVED_IRQn_Handler                        /*!< Reserved Interrupt                               */
    .long SSP1_IRQn_Handler                            /*!< SSP1 Interrupt  - new name                       */
    .long I2C_IRQn_Handler                             /*!< I2C Interrupt                                    */
    .long TIMER_16_0_IRQn_Handler                      /*!< 16-bit Timer0 Interrupt                          */
    .long TIMER_16_1_IRQn_Handler                      /*!< 16-bit Timer1 Interrupt                          */
    .long TIMER_32_0_IRQn_Handler                      /*!< 32-bit Timer0 Interrupt                          */
    .long TIMER_32_1_IRQn_Handler                      /*!< 32-bit Timer1 Interrupt                          */
    .long SSP0_IRQn_Handler                            /*!< SSP0 Interrupt  - new name                       */
    .long UART0_IRQHandler                             /*!< UART Interrupt                                   */
    .long USB_IRQn_Handler                             /*!< USB Regular Interrupt                            */
    .long USB_FIQn                                     /*!< USB Fast Interrupt                               */
    .long ADC_IRQn_Handler                             /*!< A/D Converter Interrupt                          */
    .long WDT_IRQn_Handler                             /*!< Watchdog timer Interrupt                         */  
    .long BOD_IRQn_Handler                             /*!< Brown Out Detect(BOD) Interrupt                  */
    .long RESERVED_IRQn_Handler                        /*!< Flash Interrupt                                  */
    .long RESERVED_IRQn_Handler                        /*!< Reserved Interrupt                               */
    .long RESERVED_IRQn_Handler                        /*!< Reserved Interrupt                               */
    .long RESERVED_IRQn_Handler                        /*!< USB Wakeup Interrupt                             */
    .long RESERVED_IRQn_Handler                        /*!< Reserved Interrupt                               */
    .endif
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
    LDR     R0,=initLowLevelCpu
    BLX     R0

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
/* baptiste : weak : ca dit que le code est peut etre defini plus tard ailleurs (ou pas) */
    .weak   \handler
    .set    \handler, Default_Handler
    .endm
    
    IRQ WAKEUP_IRQn_Handler                          /*!< All I/O pins can be used as wakeup source.       */
    IRQ  SSP1_IRQn_Handler
    IRQ  I2C_IRQn_Handler                             /*!< I2C Interrupt                                    */
    IRQ  TIMER_16_0_IRQn_Handler                      /*!< 16-bit Timer0 Interrupt                          */
    IRQ  TIMER_16_1_IRQn_Handler                      /*!< 16-bit Timer1 Interrupt                          */
    IRQ  TIMER_32_0_IRQn_Handler                      /*!< 32-bit Timer0 Interrupt                          */
    IRQ  TIMER_32_1_IRQn_Handler                      /*!< 32-bit Timer1 Interrupt                          */
    IRQ  SSP0_IRQn_Handler                            /*!< SSP0 Interrupt  - new name                                   */
    IRQ  UART0_IRQHandler                            /*!< UART Interrupt                                   */
    IRQ  USB_IRQn_Handler                             /*!< USB Regular Interrupt                            */
    IRQ  USB_FIQn                             /*!< USB Fast Interrupt                               */
    IRQ  ADC_IRQn_Handler                             /*!< A/D Converter Interrupt                          */
    IRQ  WDT_IRQn_Handler                             /*!< Watchdog timer Interrupt                         */  
    IRQ  BOD_IRQn_Handler                             /*!< Brown Out Detect(BOD) Interrupt                  */
    IRQ  RESERVED_IRQn_Handler                        /*!< Reserved Interrupt                               */
.if McuLpc1315 == 0
    IRQ  EINT3_IRQn_Handler                           /*!< External Interrupt 3 Interrupt                   */
    IRQ  EINT2_IRQn_Handler                           /*!< External Interrupt 2 Interrupt                   */
    IRQ  EINT1_IRQn_Handler                           /*!< External Interrupt 1 Interrupt                   */
    IRQ  EINT0_IRQn_Handler                           /*!< External Interrupt 0 Interrupt                   */
.endif

.if McuLpc1315 == 1
    IRQ PIN_INT0_IRQHandler
    IRQ PIN_INT1_IRQHandler
    IRQ PIN_INT2_IRQHandler
    IRQ PIN_INT3_IRQHandler
    IRQ PIN_INT4_IRQHandler
    IRQ PIN_INT5_IRQHandler
    IRQ PIN_INT6_IRQHandler
    IRQ PIN_INT7_IRQHandler
    IRQ GINT0_IRQHandler
    IRQ GINT1_IRQHandler
.endif

    .end
