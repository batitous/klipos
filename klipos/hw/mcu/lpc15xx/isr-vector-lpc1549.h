
    /** Interrupt service routine for LPC1549 */

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
