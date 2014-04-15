
    /** Interrupt service routine for LPC15xx */

    WDT_IRQHandler,                    //  0 - Windowed watchdog timer
    BOD_IRQHandler,                    //  1 - BOD
    FMC_IRQHandler,                    //  2 - Flash controller
    EEPROM_IRQHandler,                 //  3 - EEPROM controller
    DMA_IRQHandler,                    //  4 - DMA
    GINT0_IRQHandler,                  //  5 - GINT0
    GINT1_IRQHandler,                  //  6 - GINT1
    PIN_INT0_IRQHandler,               //  7 - PIO INT0
    PIN_INT1_IRQHandler,               //  8 - PIO INT1
    PIN_INT2_IRQHandler,               //  9 - PIO INT2
    PIN_INT3_IRQHandler,               // 10 - PIO INT3
    PIN_INT4_IRQHandler,               // 11 - PIO INT4
    PIN_INT5_IRQHandler,               // 12 - PIO INT5
    PIN_INT6_IRQHandler,               // 13 - PIO INT6
    PIN_INT7_IRQHandler,               // 14 - PIO INT7
    RIT_IRQHandler,                    // 15 - RIT
    SCT0_IRQHandler,                   // 16 - State configurable timer
    SCT1_IRQHandler,                   // 17 - State configurable timer
    SCT2_IRQHandler,                   // 18 - State configurable timer
    SCT3_IRQHandler,                   // 19 - State configurable timer
    MRT_IRQHandler,                    // 20 - Multi-Rate Timer
    UART0_IRQHandler,                  // 21 - UART0
    UART1_IRQHandler,                  // 22 - UART1
    UART2_IRQHandler,                  // 23 - UART2
    I2C0_IRQHandler,                   // 24 - I2C0 controller
    SPI0_IRQHandler,                   // 25 - SPI0 controller
    SPI1_IRQHandler,                   // 26 - SPI1 controller
    CAN_IRQHandler,                    // 27 - C_CAN0
    USB_IRQHandler,                    // 28 - USB IRQ
    USB_FIQHandler,                    // 29 - USB FIQ
    USBWakeup_IRQHandler,              // 30 - USB wake-up
    ADC0A_IRQHandler,              // 31 - ADC0 sequence A completion
    ADC0B_IRQHandler,              // 32 - ADC0 sequence B completion
    ADC0_THCMP_IRQHandler,             // 33 - ADC0 threshold compare
    ADC0_OVR_IRQHandler,               // 34 - ADC0 overrun
    ADC1A_IRQHandler,              // 35 - ADC1 sequence A completion
    ADC1B_IRQHandler,              // 36 - ADC1 sequence B completion
    ADC1_THCMP_IRQHandler,             // 37 - ADC1 threshold compare
    ADC1_OVR_IRQHandler,               // 38 - ADC1 overrun
    DAC_IRQHandler,                    // 39 - DAC
    ACMP0_IRQHandler,                   // 40 - Analog Comparator 0
    ACMP1_IRQHandler,                   // 41 - Analog Comparator 1
    ACMP2_IRQHandler,                   // 42 - Analog Comparator 2
    ACMP3_IRQHandler,                   // 43 - Analog Comparator 3
    QEI_IRQHandler,                    // 44 - QEI
    RTC_ALARM_IRQHandler,              // 45 - RTC alarm
    RTC_WAKE_IRQHandler,               // 46 - RTC wake-up
