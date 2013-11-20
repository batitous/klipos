//
// gcc startup for LPC core
// Kamal Mostafa <kamal@whence.com>
//
// License: mixed
// - simple crt0 and statically allocated stack (Kamal Mostafa; Public Domain)
// - Note: empty boilerplate ISR routines from cr_startup_lpc8xx.c
//



//*****************************************************************************
//
// Allocated stack space
//
//*****************************************************************************
#define STACKSIZE 64

static unsigned int StackMem[STACKSIZE];
#define _pStackTop ((void *)((unsigned int)StackMem + sizeof(StackMem)))

//*****************************************************************************

#define WEAK __attribute__ ((weak))
#define ALIAS(f) __attribute__ ((weak, alias (#f)))

//*****************************************************************************
//
// Forward declaration of the default handlers. These are aliased.
// When the application defines a handler (with the same name), this will
// automatically take precedence over these weak definitions
//
//*****************************************************************************

WEAK void Reset_Handler(void);
WEAK void NMI_Handler(void);
WEAK void HardFault_Handler(void);
WEAK void MemManage_Handler(void);
WEAK void BusFault_Handler(void);
WEAK void UsageFault_Handler(void);
WEAK void SVC_Handler(void);
WEAK void DebugMon_Handler(void);
WEAK void PendSV_Handler(void);
WEAK void SysTick_Handler(void);
WEAK void IntDefaultHandler(void);

//*****************************************************************************
//
// Forward declaration of the specific IRQ handlers. These are aliased
// to the IntDefaultHandler, which is a 'forever' loop. When the application
// defines a handler (with the same name), this will automatically take
// precedence over these weak definitions
//
//*****************************************************************************

//MCU_IS_LPC1311
void WAKEUP_IRQn_Handler(void) ALIAS(IntDefaultHandler);
void I2C_IRQn_Handler(void) ALIAS(IntDefaultHandler);
void TIMER_16_0_IRQn_Handler(void) ALIAS(IntDefaultHandler);
void TIMER_16_1_IRQn_Handler(void) ALIAS(IntDefaultHandler);
void TIMER_32_0_IRQn_Handler(void) ALIAS(IntDefaultHandler);
void TIMER_32_1_IRQn_Handler(void) ALIAS(IntDefaultHandler);
void SSP0_IRQn_Handler(void) ALIAS(IntDefaultHandler);
void UART0_IRQHandler(void) ALIAS(IntDefaultHandler);
void USB_IRQn_Handler(void) ALIAS(IntDefaultHandler);
void USB_FIQn(void) ALIAS(IntDefaultHandler);
void ADC_IRQn_Handler(void) ALIAS(IntDefaultHandler);
void WDT_IRQn_Handler(void) ALIAS(IntDefaultHandler);
void BOD_IRQn_Handler(void) ALIAS(IntDefaultHandler);
void RESERVED_IRQn_Handler(void) ALIAS(IntDefaultHandler);
void EINT3_IRQn_Handler(void) ALIAS(IntDefaultHandler);
void EINT2_IRQn_Handler(void) ALIAS(IntDefaultHandler);
void EINT1_IRQn_Handler(void) ALIAS(IntDefaultHandler);
void EINT0_IRQn_Handler(void) ALIAS(IntDefaultHandler);




#ifdef MCU_IS_LPC1315
void PIN_INT0_IRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT1_IRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT2_IRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT3_IRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT4_IRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT5_IRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT6_IRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT7_IRQHandler(void) ALIAS(IntDefaultHandler);
void GINT0_IRQHandler(void) ALIAS(IntDefaultHandler);
void GINT1_IRQHandler(void) ALIAS(IntDefaultHandler);
void RESERVED_IRQn_Handler(void) ALIAS(IntDefaultHandler);
void SSP1_IRQn_Handler(void) ALIAS(IntDefaultHandler);
void I2C_IRQn_Handler(void) ALIAS(IntDefaultHandler);
void TIMER_16_0_IRQn_Handler(void) ALIAS(IntDefaultHandler);
void TIMER_16_1_IRQn_Handler(void) ALIAS(IntDefaultHandler);
void TIMER_32_0_IRQn_Handler(void) ALIAS(IntDefaultHandler);
void TIMER_32_1_IRQn_Handler(void) ALIAS(IntDefaultHandler);
void SSP0_IRQn_Handler(void) ALIAS(IntDefaultHandler);
void UART0_IRQHandler(void) ALIAS(IntDefaultHandler);
void USB_IRQn_Handler(void) ALIAS(IntDefaultHandler);
void USB_FIQn(void) ALIAS(IntDefaultHandler);
void ADC_IRQn_Handler(void) ALIAS(IntDefaultHandler);
void WDT_IRQn_Handler(void) ALIAS(IntDefaultHandler);
void BOD_IRQn_Handler(void) ALIAS(IntDefaultHandler);
#endif


//*****************************************************************************
//
// The vector table.
// This relies on the linker script to place at correct location in memory.
//
//*****************************************************************************
extern void (* const g_pfnVectors[])(void);

__attribute__ ((section(".isr_vector")))
void (* const g_pfnVectors[])(void) = {

    // Core Level - CM3
    
    _pStackTop,                  /* Top of Stack                 */
    Reset_Handler,               /* Reset Handler                */
    NMI_Handler,                 /* NMI Handler                  */
    HardFault_Handler,           /* Hard Fault Handler           */
    MemManage_Handler,           /* MPU Fault Handler            */
    BusFault_Handler,            /* Bus Fault Handler            */
    UsageFault_Handler,          /* Usage Fault Handler          */
    0,                           /* Checksum, see LPC1xxx manual */
    0,                           /* Reserved                     */
    0,                           /* Reserved                     */
    0,                           /* Reserved                     */
    SVC_Handler,                 /* SVCall Handler               */
    DebugMon_Handler,            /* Debug Monitor Handler        */
    0,                           /* Reserved                     */
    PendSV_Handler,              /* PendSV Handler               */
    SysTick_Handler,             /* SysTick Handler              */
    
    // Chip Level 
    WAKEUP_IRQn_Handler,        /* All I/O pins can be used as wakeup source.       */
    WAKEUP_IRQn_Handler,        /* There are 40 pins in total for LPC17xx           */
    WAKEUP_IRQn_Handler,                  
    WAKEUP_IRQn_Handler,                  
    WAKEUP_IRQn_Handler,                     
    WAKEUP_IRQn_Handler,                          
    WAKEUP_IRQn_Handler,                          
    WAKEUP_IRQn_Handler,                          
    WAKEUP_IRQn_Handler,                          
    WAKEUP_IRQn_Handler,                          
    WAKEUP_IRQn_Handler,                        
    WAKEUP_IRQn_Handler,                        
    WAKEUP_IRQn_Handler,                        
    WAKEUP_IRQn_Handler,                        
    WAKEUP_IRQn_Handler,                        
    WAKEUP_IRQn_Handler,                        
    WAKEUP_IRQn_Handler,                        
    WAKEUP_IRQn_Handler,                        
    WAKEUP_IRQn_Handler,                        
    WAKEUP_IRQn_Handler,                        
    WAKEUP_IRQn_Handler,                        
    WAKEUP_IRQn_Handler,                        
    WAKEUP_IRQn_Handler,                        
    WAKEUP_IRQn_Handler,                        
    WAKEUP_IRQn_Handler,                        
    WAKEUP_IRQn_Handler,                        
    WAKEUP_IRQn_Handler,                        
    WAKEUP_IRQn_Handler,                        
    WAKEUP_IRQn_Handler,                        
    WAKEUP_IRQn_Handler,                        
    WAKEUP_IRQn_Handler,                        
    WAKEUP_IRQn_Handler,                        
    WAKEUP_IRQn_Handler,                        
    WAKEUP_IRQn_Handler,                        
    WAKEUP_IRQn_Handler,                        
    WAKEUP_IRQn_Handler,                        
    WAKEUP_IRQn_Handler,                        
    WAKEUP_IRQn_Handler,                        
    WAKEUP_IRQn_Handler,                        
    WAKEUP_IRQn_Handler,                        
    I2C_IRQn_Handler,           /* I2C Interrupt                                    */
    TIMER_16_0_IRQn_Handler,    /* 16-bit Timer0 Interrupt                          */
    TIMER_16_1_IRQn_Handler,    /* 16-bit Timer1 Interrupt                          */
    TIMER_32_0_IRQn_Handler,    /* 32-bit Timer0 Interrupt                          */
    TIMER_32_1_IRQn_Handler,    /* 32-bit Timer1 Interrupt                          */
    SSP0_IRQn_Handler,          /* SSP0 Interrupt  - new name                                   */
    UART0_IRQHandler,           /* UART Interrupt                                   */
    USB_IRQn_Handler,           /* USB Regular Interrupt                            */
    USB_FIQn,                   /* USB Fast Interrupt                               */
    ADC_IRQn_Handler,           /* A/D Converter Interrupt                          */
    WDT_IRQn_Handler,           /* Watchdog timer Interrupt                         */  
    BOD_IRQn_Handler,           /* Brown Out Detect(BOD) Interrupt                  */
    RESERVED_IRQn_Handler,      /* Reserved Interrupt                               */
    EINT3_IRQn_Handler,         /* External Interrupt 3 Interrupt                   */
    EINT2_IRQn_Handler,         /* External Interrupt 2 Interrupt                   */
    EINT1_IRQn_Handler,         /* External Interrupt 1 Interrupt                   */
    EINT0_IRQn_Handler          /* External Interrupt 0 Interrupt                   */
    
#ifdef MCU_IS_LPC1315
    
    PIN_INT0_IRQHandler,        /* GPIO Interrupt 0 Interrupt                       */
    PIN_INT1_IRQHandler,        /* GPIO Interrupt 1 Interrupt                       */
    PIN_INT2_IRQHandler,        /* GPIO Interrupt 2 Interrupt                       */
    PIN_INT3_IRQHandler,        /* GPIO Interrupt 3 Interrupt                       */
    PIN_INT4_IRQHandler,        /* GPIO Interrupt 4 Interrupt                       */
    PIN_INT5_IRQHandler,        /* GPIO Interrupt 5 Interrupt                       */
    PIN_INT6_IRQHandler,        /* GPIO Interrupt 6 Interrupt                       */
    PIN_INT7_IRQHandler,        /* GPIO Interrupt 7 Interrupt                       */
    GINT0_IRQHandler,           /* GPIO Group 0 Interrupt                           */
    GINT1_IRQHandler,           /* GPIO Group 1 Interrupt                           */
    RESERVED_IRQn_Handler,      /* Reserved Interrupt                               */
    RESERVED_IRQn_Handler,      /* Reserved Interrupt                               */
    RESERVED_IRQn_Handler,      /* RIT Interrupt                                    */
    RESERVED_IRQn_Handler,      /* Reserved Interrupt                               */
    SSP1_IRQn_Handler,          /* SSP1 Interrupt  - new name                       */
    I2C_IRQn_Handler,           /* I2C Interrupt                                    */
    TIMER_16_0_IRQn_Handler,    /* 16-bit Timer0 Interrupt                          */
    TIMER_16_1_IRQn_Handler,    /* 16-bit Timer1 Interrupt                          */
    TIMER_32_0_IRQn_Handler,    /* 32-bit Timer0 Interrupt                          */
    TIMER_32_1_IRQn_Handler,    /* 32-bit Timer1 Interrupt                          */
    SSP0_IRQn_Handler,          /* SSP0 Interrupt  - new name                       */
    UART0_IRQHandler,           /* UART Interrupt                                   */
    USB_IRQn_Handler,           /* USB Regular Interrupt                            */
    USB_FIQn,                   /* USB Fast Interrupt                               */
    ADC_IRQn_Handler,           /* A/D Converter Interrupt                          */
    WDT_IRQn_Handler,           /* Watchdog timer Interrupt                         */  
    BOD_IRQn_Handler,           /* Brown Out Detect(BOD) Interrupt                  */
    RESERVED_IRQn_Handler,      /* Flash Interrupt                                  */
    RESERVED_IRQn_Handler,      /* Reserved Interrupt                               */
    RESERVED_IRQn_Handler,      /* Reserved Interrupt                               */
    RESERVED_IRQn_Handler,      /* USB Wakeup Interrupt                             */
    RESERVED_IRQn_Handler      /* Reserved Interrupt                               */
#endif
            
            
}; /* End of g_pfnVectors */


//*****************************************************************************
// Reset entry point for your code.
// Sets up a simple C runtime environment.
//*****************************************************************************

extern unsigned int _etext;
extern unsigned int _data;
extern unsigned int _edata;
extern unsigned int _bss;
extern unsigned int _ebss;

// Simple gcc-compatible C runtime init
static inline void crt0(void)
{
    unsigned int *src, *dest, *dend;
    
    // copy the data section
    src  = (unsigned int *)(&_etext);
    dest = (unsigned int *)(&_data);
    dend = (unsigned int *)(&_edata);
    while (dest < dend)
	*(dest++) = *(src++);
    
    // blank the bss section
    dest = (unsigned int *)(&_bss);
    dend = (unsigned int *)(&_ebss);
    while (dest < dend)
	*(dest++) = 0;
}

extern void initLowLevelCpu(void);
extern int main(void);

__attribute__ ((section(".after_vectors")))
void Reset_Handler(void)
{
    crt0();
    initLowLevelCpu();
    main();
    
    while (1) ;	// hang if main returns
}

//*****************************************************************************
// Default exception handlers. Override the ones here by defining your own
// handler routines in your application code.
//*****************************************************************************
__attribute__ ((section(".after_vectors")))
void NMI_Handler(void)
{
    while(1)
    {
    }
}
__attribute__ ((section(".after_vectors")))
void HardFault_Handler(void)
{
    while(1)
    {
    }
}
__attribute__ ((section(".after_vectors")))
void SVCall_Handler(void)
{
    while(1)
    {
    }
}
__attribute__ ((section(".after_vectors")))
void PendSV_Handler(void)
{
    while(1)
    {
    }
}
__attribute__ ((section(".after_vectors")))
void SysTick_Handler(void)
{
    while(1)
    {
    }
}

//*****************************************************************************
//
// Processor ends up here if an unexpected interrupt occurs or a specific
// handler is not present in the application code.
//
//*****************************************************************************
__attribute__ ((section(".after_vectors")))
void IntDefaultHandler(void)
{
    while(1)
    {
    }
}


