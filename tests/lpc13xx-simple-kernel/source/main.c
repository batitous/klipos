
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

Pwm mot1;
Pwm mot2;
Pwm mot3;
Pwm mot4;

void initDcMotor(void)
{
    // a partir de 100 000 us ca foire le pwm, il faut mettre un prescaler
    initPwm(&mot1, TIMER32_1, PWM0, 100, 0,0);
    initPwm(&mot2, TIMER32_1, PWM1, 100, 0,0);
    initPwm(&mot3, TIMER32_1, PWM2, 100, 0,0);
    initPwm(&mot4, TIMER32_0, PWM0, 100, 0,0);
    
    enablePwm(&mot1);
    enablePwm(&mot2);
    enablePwm(&mot3);
    enablePwm(&mot4);
}

void setDcMotor(uint32_t m1, uint32_t m2, uint32_t m3, uint32_t m4)
{
    setPwmRawDutyCycle(&mot1, m1);
    setPwmRawDutyCycle(&mot2, m2);
    setPwmRawDutyCycle(&mot3, m3);
    setPwmRawDutyCycle(&mot4, m4);
}

#define LED_PERIOD_IN_US        900

Pwm ledr;
Pwm ledg;
Pwm ledb;

void initRGBLed(void)
{
    initPwm(&ledr, TIMER16_1, PWM0, LED_PERIOD_IN_US, 0,0);
    initPwm(&ledg, TIMER16_1, PWM1, LED_PERIOD_IN_US, 0,0);
    initPwm(&ledb, TIMER16_0, PWM2, LED_PERIOD_IN_US, 0,0);
    
    enablePwm(&ledr);
    enablePwm(&ledg);
    enablePwm(&ledb);
}

void setRGBLed(uint32_t r, uint32_t g, uint32_t b)
{
    setPwmDutyCycle(&ledr, r);
    setPwmDutyCycle(&ledg, g);
    setPwmDutyCycle(&ledb, b);
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
    
    assignTaskOnUart0(&uartTask);
    
    enableGpioIrqOnTask(&gpioTask, GPIO0_1, GPIO_BOTH_EDGE);
    
    sendByteToUart0('1');
    
    initTimer(&t100, MS_TO_US(1200), &t100Task);
    initTimer(&t150, SECOND_TO_US(1), &t150Task);
    initTimer(&t333, MS_TO_US(1333), &t333Task);
    
    printf("Test Simple Kernel sizeof KTask %d !\r\n", sizeof(KTask));
    
    
    initDcMotor();
    setDcMotor(500,500,500,500);
    
    initRGBLed();
    setRGBLed(500,500,500);
    
    while(1)
    {
        scheduleTask();
    }
    
    
    return 0;
}

