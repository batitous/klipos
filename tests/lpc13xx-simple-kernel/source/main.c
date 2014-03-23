
#include <libs-klipos.h>



int main(void)
{
    initUart0();
    setPrintfInterface(sendByteToUart0);
    
    
    printf("Test Simple Kernel !\r\n");
    
    
    
    
    
    return 0;
}

