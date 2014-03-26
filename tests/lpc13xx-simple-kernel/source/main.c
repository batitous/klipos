
#include <libs-klipos.h>

#include "../include/kqueue.h"
#include "../include/ktask.h"
#include "../include/ktime.h"

KTask uartTask;
KTask t100Task;
KTask t150Task;
KTask t333Task;

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
KTime t333;

void t100TaskCode(UInt32 event)
{
    printf("100\r\n");
}

void t150TaskCode(UInt32 event)
{
    printf("150\r\n");
}

void t333TaskCode(UInt32 event)
{
    printf("333\r\n");
}


int main(void)
{
    initUart0();
    setPrintfInterface(sendByteToUart0);
    
    
    initKernel();
    initKernelTimers();
    
    initTask(&uartTask, uartTaskCode, 1, 12345);

    initTask(&t100Task, t100TaskCode, 1, 0);
    initTask(&t150Task, t150TaskCode, 1, 0);
    initTask(&t333Task, t333TaskCode, 1, 0);

    initTimer(&t100, 100*1000, &t100Task);
    initTimer(&t150, 150*1000, &t150Task);
    initTimer(&t333, 333*1000, &t333Task);
    
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

