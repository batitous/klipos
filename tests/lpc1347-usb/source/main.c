
#include <libs-klipos.h>

#include "../include/app_usbd_cfg.h"
#include "../include/cdc_vcom.h"

extern void initUsbHardware(void);
extern void initUsbStack(void);

#define LED     GPIO0_7
#define BUTTON  GPIO0_1 

KTask uartTask;
KTask gpioTask;
KTask ledTask;
KTimer ledTimer;

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
        for (i=0;i<4;++i)
        {
            printf("%c", buffer[i]);
        }
        printf("\r\n");
    }
    
}

void gpioTaskCode(uint32_t event)
{
    printf("IRQ Button: %x\r\n", event);    
}

int prompt = 0;

void ledTaskCode(uint32_t event)
{
    uint8_t buffer[1];
        
    toggleGpio(LED);
    
    if ((vcom_connected() != 0) && (prompt == 0)) 
    {
        vcom_write("Hello World!!\r\n", 15);
	prompt = 1;
    }
    
    if ((vcom_connected() != 0))
    {
        if (vcom_bread(buffer,1)!=0)
        {
            vcom_write(buffer,1);
        }
    }

}

int main(void)
{
    initGpio();
    initUart0();
    setPrintfInterface(sendByteToUart0);
    
    setGpioDirection(LED, GPIO_OUT);

    initUsbHardware();
    
    initSimpleKernel();
    
    initTask(&uartTask, uartTaskCode, PRIORITY_LOW);
    setTaskOnUart0(&uartTask);
    
    initTask(&gpioTask, gpioTaskCode, PRIORITY_LOW);
    enableGpioIrqOnTask(&gpioTask, BUTTON, GPIO_BOTH_EDGE);
    setGpioOption(BUTTON, GPIO_MODE_INACTIVE, true, false);
    
    initTask(&ledTask, ledTaskCode, PRIORITY_LOW);
    initTimer(&ledTimer, MS_TO_US(500), &ledTask);
    
    printf("Test Simple Kernel sizeof KTask %d !\r\n", sizeof(KTask));
    
    initUsbStack();
    
    while(1)
    {
        scheduleTask();
    }
    
    
    return 0;
}

