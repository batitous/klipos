
// test lpc8xx compilation system

#include <libs-klipos.h>

void configurePins()
{
    /* Pin Assign 8 bit Configuration */
    /* U0_TXD */
    /* U0_RXD */
//    LPC_SWM->PINASSIGN0 = 0xffff0004UL;

    /* Pin Assign 1 bit Configuration */
//    LPC_SWM->PINENABLE0 = 0xffffffbfUL;
    
    /* Pin Assign 1 bit Configuration */
    /* RESET */
    
//    LPC_SWM->PINENABLE0 = 0xffffffbfUL;
    
    // no reset
    LPC_SWM->PINENABLE0 = 0xffffffffUL;
}


int main(void)
{
    
    initGpio();

    configurePins();
    
    while(1)
    {

    }

    return 0;
}


