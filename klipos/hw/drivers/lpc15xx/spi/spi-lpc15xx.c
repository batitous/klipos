/*
 The MIT License (MIT)
 
 Copyright (c) 2015 Baptiste Burles
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of
 this software and associated documentation files (the "Software"), to deal in
 the Software without restriction, including without limitation the rights to
 use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 the Software, and to permit persons to whom the Software is furnished to do so,
 subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#include "../../../include/libs-klipos.h"


//--------------------- private functions

#define CLEAR_STATUS()         SETBIT(LPC_SPI0->STAT, 2); SETBIT(LPC_SPI0->STAT, 3); SETBIT(LPC_SPI0->STAT, 4); \
                                       SETBIT(LPC_SPI0->STAT, 5); SETBIT(LPC_SPI0->STAT, 7);


static void configureSpiSend(void)
{
    // select slave 0
    CLRBIT(LPC_SPI0->TXCTRL, 16);
    
    // NOT end of transfer
    CLRBIT(LPC_SPI0->TXCTRL, 20);
    // YES end of frame
    SETBIT(LPC_SPI0->TXCTRL, 21);
    // YES, rx ignored
    SETBIT(LPC_SPI0->TXCTRL, 22);
}


static void sendSpiWithEnd(uint8_t data, bool isEndOfTrame)
{
    while (!(LPC_SPI0->STAT & BIT(1))) {}
    
    if (isEndOfTrame==true)
    {
        SETBIT(LPC_SPI0->TXCTRL, 20);
    }
    
    LPC_SPI0->TXDAT = (data && 0xff);
}

static uint8_t getSpi(void)
{
    while ( (LPC_SPI0->STAT & BIT(0))==0);
    return (LPC_SPI0->RXDAT & 0xff);
}

//--------------------- public functions

void initSpi(SpiMode mode)
{
    
    SETBIT(LPC_SYSCON->SYSAHBCLKCTRL[1],9);
    SETBIT(LPC_SYSCON->PRESETCTRL[1], 9);
    CLRBIT(LPC_SYSCON->PRESETCTRL[1], 9);
    
    // disable
    CLRBIT(LPC_SPI0->CFG, 0);
    
    // master mode
    SETBIT(LPC_SPI0->CFG, 2);
    
    // select Chip Select 0 active low
    CLRBIT(LPC_SPI0->CFG, 8);
    
    switch(mode)
    {
        case SPI_MODE0:
            // cpol = 0 cpha = 0
            CLRBIT(LPC_SPI0->CFG, 4);
            CLRBIT(LPC_SPI0->CFG, 5);
            break;
        case SPI_MODE1:
            // cpol = 0 cpha = 1
            SETBIT(LPC_SPI0->CFG, 4);
            CLRBIT(LPC_SPI0->CFG, 5);
            break;
        case SPI_MODE2:
            // cpol = 1 cpha = 0
            CLRBIT(LPC_SPI0->CFG, 4);
            SETBIT(LPC_SPI0->CFG, 5);
            break;
        case SPI_MODE3:
            // cpol = 1 cpha = 1
            SETBIT(LPC_SPI0->CFG, 4);
            SETBIT(LPC_SPI0->CFG, 5);
            break;
    }
    
    // clock 4 MHz
#define SPI_CLOCK       4000
    
    LPC_SPI0->DIV = (KERNEL_CPU_FREQ + (SPI_CLOCK - 1))/SPI_CLOCK - 1;
    LPC_SPI0->DLY = 0;
    
    CLEAR_STATUS();
    
    // 8 bits of data
    LPC_SPI0->TXCTRL = BITS(24, 7);
    
    
    SETBIT(LPC_SPI0->TXCTRL, 16);
    SETBIT(LPC_SPI0->TXCTRL, 17);
    SETBIT(LPC_SPI0->TXCTRL, 18);
    SETBIT(LPC_SPI0->TXCTRL, 19);
    
    // enable
    SETBIT(LPC_SPI0->CFG, 0);
    
}


uint8_t sendByteToSpi(uint8_t data)
{
    sendSpiWithEnd(data, true);
    
    return 0;
}

void sendBufferToSpi(uint8_t *buffer, uint32_t size)
{
    uint32_t i;
    
    CLEAR_STATUS();
    
    SETBIT(LPC_SPI0->TXCTRL, 22);
    
    for (i=0; i < size; i++)
    {
        sendSpiWithEnd(buffer[i], true);
    }
}

void getBufferFromSpi(uint8_t *buffer, uint32_t size)
{
    uint32_t i;
    
    CLEAR_STATUS();
    
    CLRBIT(LPC_SPI0->TXCTRL, 22);
    
    for (i=0; i < size; i++)
    {
        sendSpiWithEnd(0x55, true);
        buffer[i] = getSpi();
    }
}

/*uint8_t sendByteToSpi(uint8_t data)
{
    CLEAR_STATUS();
    
    configureSpiSend();
 
    sendSpiWithEnd(data, true);
    
    return 0;
}

void sendBufferToSpiAndCloseTransfer(uint8_t * buffer, uint32_t size, bool end)
{
    CLEAR_STATUS();
    
    configureSpiSend();
    
//    printf("spi conf\r\n");
    
    uint32_t i;
    for (i=0; i < size-1; i++)
    {
        sendSpiWithEnd(buffer[i], false);
    }
    
    sendSpiWithEnd(buffer[i], end);
    
    // Make sure the last frame sent completely
    if (end==true)
    {
        while (( LPC_SPI0->STAT & BIT(5)) == 0);
        SETBIT(LPC_SPI0->STAT, 5);
    }
    
}

void sendBufferToSpi(uint8_t *buffer, uint32_t size)
{
    sendBufferToSpiAndCloseTransfer(buffer, size, true);
}

void getBufferFromSpi(uint8_t *buffer, uint32_t size)
{
    CLEAR_STATUS();
        
    // 8 bits of data
    LPC_SPI0->TXCTRL = BITS(24, 7);

    // select slave 0
    CLRBIT(LPC_SPI0->TXCTRL, 16);
    
    // NOT end of transfer
    CLRBIT(LPC_SPI0->TXCTRL, 20);
    // YES end of frame
    SETBIT(LPC_SPI0->TXCTRL, 21);
    // rx not ignored
    CLRBIT(LPC_SPI0->TXCTRL, 22);
    
    uint32_t i;
    for (i=0; i < size -1; i++)
    {
        sendSpiWithEnd(0x55, false);
        buffer[i] = getSpi();
    }

    sendSpiWithEnd(0x55, true);
    buffer[i] = getSpi();
    
}

uint8_t getByteFromSpi(void)
{
    uint8_t buffer[1];
    getBufferFromSpi(buffer, 1);
    return buffer[0];
}
*/

