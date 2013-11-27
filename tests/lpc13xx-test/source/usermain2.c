
#include <libs-klipos.h>

const Uart * uart0;

Pwm pwm1;

void irqCallback(UInt32 gpioEvent, UInt32 gpioEdge)
{
    printf("%5d irq %x e %x\r\n", getSystickCounter(), gpioEvent, gpioEdge);
}

int main(void)
{
    UInt8 data;
    UInt8 buffer[6];
    
    uart0 = initUart0();
    setPrintfInterface(sendByteToUart0);

    initSystickTimer(1000);
    
    printf("Hello from test !\r\n");
    
    setGpioIrqCallback(irqCallback);
    enableGpioIrq(GPIO0_1, GPIO_FALLING_EDGE);
    

    setGpioDirection(GPIO0_10,GPIO_OUT);
    CLRBIT(LPC_GPIO0->DATA,10);
    
    initPwm(&pwm1, TIMER16_0, PWM0 | PWM1 , 1, 0, 100);
    
    
    enablePwm(&pwm1);
    waitUsPrecise(TIMER0,2);
        
    disablePwm(&pwm1);
        
    setPwmDutyCycle(&pwm1,800);
    enablePwm(&pwm1);
    
    while(1)
    {
        /*if (uart0->readByte(&data)==true)
        {
            uart0->writeByte(data+1);
        }*/
        
        
        if (uart0->read(buffer,6)==6)
        {
            uart0->write(buffer,6);
        }
    }

    return 0;
}


