

#include <libs-default.h>
#include <kernel-klipos.h>

void powerOnUart0(void)
{
    // enable uart clock
#ifdef MCU_IS_LPC13XX
    SETBIT(LPC_SYSCON->SYSAHBCLKCTRL,12);
    LPC_SYSCON->USARTCLKDIV = 1;
#endif
}

#ifdef MCU_IS_LPC1311

void setUartIoCon(void)
{
    CLRBITS(LPC_IOCON->PIO1_6,7);
    LPC_IOCON->PIO1_6 |= 1;
    
    CLRBITS(LPC_IOCON->PIO1_7,7);
    LPC_IOCON->PIO1_7 |= 1;
    
    powerOnUart0();
}
#endif

#ifdef MCU_IS_LPC1315

void setUartIoCon(void)
{
    CLRBITS(LPC_IOCON->PIO0_19,7);
    LPC_IOCON->PIO0_19 |= 1;
    
    CLRBITS(LPC_IOCON->PIO0_18,7);
    LPC_IOCON->PIO0_18 |= 1;
    
    powerOnUart0();
}
#endif

#ifdef MCU_IS_LPC13XX

//115200
#               define setBaudrate()    LPC_UART0->DLL = 39; LPC_UART0->DLM = 0;
//57600
//#               define setBaudrate()    LPC_UART0->DLL = 78; LPC_UART0->DLM = 0;
//38400
//#       define setBaudrate()    LPC_UART0->DLL = 117; LPC_UART0->DLM = 0;
#endif


#ifdef MCU_IS_LPC17XX

void setUartIoCon(void)
{
    // how to compute uart baudrate:
    //
    // uartbaudrate = PCLK / ( 16 x ( 256 x UART0_DLM + UART0_DLL ) )
    // with PCLK = 72MHz
    
    LPC_PINCON->PINSEL0  |= 0x50;
}

#       define setBaudrate()    LPC_UART0->DLL = 27; LPC_UART0->DLM = 0;

#endif


#define UART_BUFFER_SIZE    64


//--------------------- private variables:

static KIOStream uartStream;
static UInt8 uartBuffer[UART_BUFFER_SIZE];


//--------------------- private functions:

void UART0_IRQHandler(void)
{
    UInt32 status = LPC_UART0->IIR;
    
    //Check if interrupt is pending
    if( (status & 1)==0)
    {
        status = (status >> 1) & 0x07;
        
        //Receive Data Available
        if(status==0x02)
        {
            writeByteToIOStream(&uartStream,LPC_UART0->RBR);
            irqWakeUpTaskFromIOStream(&uartStream);
        }
    }
}

//--------------------- public functions:



void powerOffUart0(void)
{
#ifdef MCU_IS_LPC13XX
    CLRBIT(LPC_SYSCON->SYSAHBCLKCTRL,12);
    LPC_SYSCON->USARTCLKDIV = 0;
#endif
}

void initUart0(void)
{
    initIOStream(&uartStream,uartBuffer,UART_BUFFER_SIZE);
    
    setUartIoCon();
    
    LPC_UART0->FCR = 0x7;   // enable and reset fifos
    LPC_UART0->LCR = 0x83;	// 8 bits; enable divisor latches
    
    setBaudrate();
    
    LPC_UART0->LCR=3;
    
    LPC_UART0->IER = BIT(0);    // enable receive interrupt
    
    
    NVIC_SetPriority(UART0_IRQn, 0x04);
    NVIC_EnableIRQ(UART0_IRQn); // enable NVIC UART0 Interrupt
}

void sendByteToUart0(UInt8 byte)
{
	while( (LPC_UART0->LSR & BIT(5) ) ==0 );
    
	// test bit-band memory : LSR register is at +0x14 from the base UART memory
    //	while( ( BITBAND( LPC_UART0_BASE + 0x14, 5) )  == 0 );
    
	LPC_UART0->THR=byte;
}

void sendBufferToUart0(UInt8 * Buffer,UInt32 Count)
{
    UInt32 i;
    
    for(i=0;i<Count;i++)
    {
        sendByteToUart0(Buffer[i]);
    }
}

UInt32 getBufferFromUart0(UInt8 * buffer, UInt32 len)
{
    return readBufferFromIOStream(&uartStream, buffer, len);
}

bool getByteFromUart0(UInt8 *data)
{
    return readByteFromIOStream(&uartStream, data);
}

KThread threadLed;
UInt8 threadLedStack[256];


void led(void)
{
    UInt8 data;
    
    printf("Thread is runing !\r\n");
    
    UInt8 * m = malloc(1000);
    UInt32 i;
    
    while(1)
    {
        waitDataFromIOStream(&uartStream);
        
         for(i=0;i<1000;i++)
             m[i] = 0xAA;
        
        if (getByteFromUart0(&data)==True)
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
                
                sendByteToUart0(data+1);
            }
        }
        
        
    }
}

KMemory * defaultMemory;

int usermain(void)
{
    initUart0();
    setPrintfInterface(sendByteToUart0);
    
 
    // memory init
    // the _ebss variable comes from the linker script
    // _ebss store the address where free memory begins
    
    extern unsigned int _ebss;
    defaultMemory = initMemory( (UInt8 *)&_ebss,1024);
    
   
    printf("Hello from KLIPOS :-)\r\n");
    
    initThread( &threadLed, led, threadLedStack, 256, 10, 5);
    
   
    
    return 0;
}

