// Core Level - CM0plus
    _pStackTop, //&_vStackTop,		// The initial stack pointer
    Reset_Handler,				// The reset handler
    NMI_Handler,			// The NMI handler
    HardFault_Handler,			// The hard fault handler
    0,					// Reserved
    0,					// Reserved
    0,					// Reserved
    0,					// Reserved
    0,					// Reserved
    0,					// Reserved
    0,					// Reserved
    SVC_Handler,			// SVCall handler
    0,					// Reserved
    0,					// Reserved
    PendSV_Handler,			// The PendSV handler
    SysTick_Handler,			// The SysTick handler

	// Chip Level - LPC8xx
    SPI0_IRQHandler,                         // SPI0 controller
    SPI1_IRQHandler,                         // SPI1 controller
    0,                                       // Reserved
    UART0_IRQHandler,                        // UART0
    UART1_IRQHandler,                        // UART1
    UART2_IRQHandler,                        // UART2
    0,                                       // Reserved
    0,                                       // Reserved
    I2C_IRQHandler,                          // I2C controller
    SCT_IRQHandler,                          // Smart Counter Timer
    MRT_IRQHandler,                          // Multi-Rate Timer
    CMP_IRQHandler,                          // Comparator
    WDT_IRQHandler,                          // PIO1 (0:11)
    BOD_IRQHandler,                          // Brown Out Detect
    0,                                       // Reserved
    WKT_IRQHandler,                          // Wakeup timer
    0,                                       // Reserved
    0,                                       // Reserved
    0,                                       // Reserved
    0,                                       // Reserved
    0,                                       // Reserved
    0,                                       // Reserved
    0,                                       // Reserved
    0,                                       // Reserved
    PININT0_IRQHandler,                      // PIO INT0
    PININT1_IRQHandler,                      // PIO INT1
    PININT2_IRQHandler,                      // PIO INT2
    PININT3_IRQHandler,                      // PIO INT3
    PININT4_IRQHandler,                      // PIO INT4
    PININT5_IRQHandler,                      // PIO INT5
    PININT6_IRQHandler,                      // PIO INT6
    PININT7_IRQHandler,                      // PIO INT7