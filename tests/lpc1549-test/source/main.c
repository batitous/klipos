
#include <libs-klipos.h>



KTask uartTask;
KTask timerTask;

KTimer myTimer;

void timerTaskCode(uint32_t event)
{
    printf("Timer !\r\n");
}

void uartTaskCode(uint32_t event)
{
//    printf("Receive: %c\r\n", (int8_t)event);
    
    uint32_t i;
    uint8_t buffer[4];
    uint32_t lenReceived;
    
    lenReceived = getBufferFromUart0(buffer,4);
    if (lenReceived == 4)
    {
        printf("Received: ");
        for (i=0;i<4;i++)
        {
            printf("%c", buffer[i]);
        }
        printf("\r\n");
    }
    
}


int main(void)
{
    // enable IOCON clock
//    SETBIT(LPC_SYSCON->SYSAHBCLKCTRL[0],13);
    
    initSwitchMatrix();
    
    assignMovableFunctionToGpio(SWM_UART0_RXD_I , GPIO0_13);
    assignMovableFunctionToGpio(SWM_UART0_TXD_O , GPIO0_18);
    
    initUart0();
    setPrintfInterface(sendByteToUart0);
    
    sendByteToUart0('1');
    sendByteToUart0(' ');
    sendByteToUart0('3');
    sendByteToUart0(' ');
    
    initSimpleKernel();
    
    initTask(&uartTask, uartTaskCode, PRIORITY_LOW);
    setTaskOnUart0(&uartTask);
    
    initTask(&timerTask, timerTaskCode, PRIORITY_LOW);
    initTimer(&myTimer, MS_TO_US(500), &timerTask);
    
    printf("Test Simple Kernel sizeof KTask %d !\r\n", sizeof(KTask));
    
    
    while(1)
    {
        scheduleTask();
    }
    
    
    return 0;
}

