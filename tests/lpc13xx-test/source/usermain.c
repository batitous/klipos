

#include <libs-klipos.h>


KThread threadLed;
UInt8 threadLedStack[256];

const Uart * uart0;

Pwm pwm1;
Pwm pwm2;


void led(void)
{
    UInt8 data;
    
    printf("Thread is runing !\r\n");
    
    UInt8 * m = malloc(1000);
    UInt32 i;
    
    while(1)
    {
        uart0->wait();
        
         for(i=0;i<1000;i++)
             m[i] = 0xAA;
        
        if (uart0->readByte(&data)==True)
        {
            if (data=='d')
            {
                dumpKernel();
            }
            else
            {
                for(i=0;i<1000;i++)
                {
                    m[i] = 0xAA;
                }
                
                uart0->writeByte(data+1);
            }
        }
        
        
    }
}

KAlarm myAlarm;
KEventManager myAlarmManager;


void myAlarmCallback(KEvent *e)
{
    printf("Callback alarm at %d!\r\n", e->time);
}

KMemory * defaultMemory;

int usermain(void)
{
    uart0 = initUart0();
    setPrintfInterface(sendByteToUart0);
    
    initEventManager();
 
    // memory init
    // the _ebss variable comes from the linker script
    // _ebss store the address where free memory begins
    
    extern unsigned int _ebss;
    defaultMemory = initMemory( (UInt8 *)&_ebss,1024);
    
   
    printf("Hello from KLIPOS :-)\r\n");
    
    initThread( &threadLed, led, threadLedStack, 256, 10, 5);
    
    initAlarm(&myAlarm,700);
    enableEventOnAlarm(&myAlarm, &myAlarmManager, myAlarmCallback,0);
    startAlarm(&myAlarm);
    
    
    setGpioDirection(GPIO0_10,GPIO_OUT);
    CLRBIT(LPC_GPIO0->DATA,10);
    
    initPwm(&pwm1, TIMER16_0, PWM0 | PWM1 , 1, 0, 100);
    
    
//    SETBIT(LPC_GPIO0->DATA,10);
    
    enablePwm(&pwm1, True);
    waitUsPrecise(TIMER0,2);
    
//    CLRBIT(LPC_GPIO0->DATA,10);
//    SETBIT(LPC_GPIO0->DATA,10);
    
    enablePwm(&pwm1, False);
    
//    CLRBIT(LPC_GPIO0->DATA,10);
    
    setPwmDutyCycle(&pwm1,800);
    enablePwm(&pwm1, True);
//    SETBIT(LPC_GPIO0->DATA,10);
    
    while(1);
    
    return 0;
}

