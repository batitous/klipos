
#include <libs-klipos.h>

#include "../include/kqueue.h"
#include "../include/ktask.h"
#include "../include/ktime.h"

KTask uartTask;


void uartTaskCode(UInt32 event)
{
//    printf("Receive: %c\r\n", (Int8)event);
    
    UInt32 i;
    UInt8 buffer[4];
    UInt32 lenReceived;
    
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


KTime t100;
KTime t150;

int main(void)
{
    initUart0();
    setPrintfInterface(sendByteToUart0);
    
    
    initKernel();
    initKernelTimers();
    
    initTask(&uartTask, uartTaskCode, 1, 12345);

    initTimer(&t100, 100*1000);
    initTimer(&t150, 150*1000);
    
    
    printf("Test Simple Kernel sizeof KTask %d !\r\n", sizeof(KTask));
    
    debugTimer();
    
    while(1)
    {
        if (scheduleTask()==false)
        {
            executeIdleTask();
        }
    }
    
    
    return 0;
}

