
    /** Interrupt service routine for LPC1311 */

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
        
