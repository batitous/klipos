
#include <libs-klipos.h>


KTask uartTask;
KTask t100Task;
KTask t150Task;
KTask t333Task;
KTask gpioTask;


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

void gpioTaskCode(uint32_t event)
{
    printf("IRQ event: %x\r\n", event);
}


KTimer t100;
KTimer t150;
KTimer t333;

bool t100Ok;
bool t150Ok;

void t100TaskCode(uint32_t event)
{
//    printf("100\r\n");
    
    if (t100Ok==false)
    {
        setGpioValue(GPIO1_31,0);
        t100Ok = true;
    }
    else
    {
        setGpioValue(GPIO1_31,1);
        t100Ok = false;
    }
}

void t150TaskCode(uint32_t event)
{
    //printf("150\r\n");
    if (t150Ok==false)
    {
        setGpioValue(GPIO0_9,0);
        t150Ok = true;
    }
    else
    {
        setGpioValue(GPIO0_9,1);
        t150Ok = false;
    }
}

void t333TaskCode(uint32_t event)
{
    //printf("333\r\n");
}


int main(void)
{
    initGpio();
    initUart0();
    setPrintfInterface(sendByteToUart0);
    
    t100Ok = false;
    setGpioDirection(GPIO1_31, GPIO_OUT);
    
    t150Ok = false;
    setGpioDirection(GPIO0_9, GPIO_OUT);
    
    initSimpleKernel();
    
    initTask(&uartTask, uartTaskCode, PRIORITY_LOW);

    initTask(&t100Task, t100TaskCode, PRIORITY_LOW);
    initTask(&t150Task, t150TaskCode, PRIORITY_VERY_HIGH);
    initTask(&t333Task, t333TaskCode, PRIORITY_HIGH);
    initTask(&gpioTask, gpioTaskCode, PRIORITY_LOW);
    
    setTaskOnUart0(&uartTask);
    
    enableGpioIrqOnTask(&gpioTask, GPIO0_1, GPIO_BOTH_EDGE);
    
    initTimer(&t100, MS_TO_US(1200), &t100Task);
    initTimer(&t150, SECOND_TO_US(1), &t150Task);
    initTimer(&t333, MS_TO_US(1333), &t333Task);
    
    printf("Test Simple Kernel sizeof KTask %d !\r\n", sizeof(KTask));
    
    while(1)
    {
        scheduleTask();
    }
    
    
    return 0;
}

