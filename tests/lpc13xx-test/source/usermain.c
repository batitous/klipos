

//#include <libs-hardware.h>
#include <kernel-klipos.h>


KThread threadLed;
UInt8 threadLedStack[256];


void led(void)
{
    
    while(1)
    {
        
        
        waitMs(50);
        
    }
}


int usermain(void)
{
   

    initThread( &threadLed, led, threadLedStack, 512, 10, 5);
    
   
    
    return 0;
}

