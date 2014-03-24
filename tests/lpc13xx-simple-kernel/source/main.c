
#include <libs-klipos.h>

#include "../include/kqueue.h"
#include "../include/ktask.h"

KTask uartTask;


void uartTaskCode(UInt32 event)
{
    printf("Receive: %c\r\n", (Int8)event);
}

int main(void)
{
    initUart0();
    setPrintfInterface(sendByteToUart0);
    
    
    initKernel();
    initTask(&uartTask, uartTaskCode, 1, 12345);

    
    printf("Test Simple Kernel !\r\n");
    
    
    while(1)
    {
        if (scheduleTask()==false)
        {
            executeIdleTask();
        }
    }
    
    
    return 0;
}

