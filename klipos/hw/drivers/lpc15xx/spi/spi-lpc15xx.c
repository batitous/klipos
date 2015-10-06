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

#define SPI_CLOCK_DIVIDER      17 
#define CLEAR_STATUS()         LPC_SPI0->STAT = BITS(2, 0x2F)


static void configureSpiSend(void)
{
    // 8 bits of data
    LPC_SPI0->TXCTRL = BITS(24, 7);

    // select slave 0
    CLRBIT(LPC_SPI0->TXCTRL, 16);
    SETBIT(LPC_SPI0->TXCTRL, 17);
    SETBIT(LPC_SPI0->TXCTRL, 18);
    SETBIT(LPC_SPI0->TXCTRL, 19);
    
    // NOT end of transfer
    CLRBIT(LPC_SPI0->TXCTRL, 20);
    // NOT end of frame
    CLRBIT(LPC_SPI0->TXCTRL, 21);
    // YES, rx ignored
    SETBIT(LPC_SPI0->TXCTRL, 22);
}

static void sendSpiEndOfTrame(uint8_t data)
{
    while ( (LPC_SPI0->STAT & BIT(1))==0);
    SETBIT(LPC_SPI0->TXCTRL, 20);
    LPC_SPI0->TXDAT = data;
}

static void sendSpi(uint8_t data)
{
    while ( (LPC_SPI0->STAT & BIT(1))==0);
    LPC_SPI0->TXDAT = data;
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
    SETBIT(LPC_SPI0->CFG, 1);
    
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
    LPC_SPI0->DIV = 0xFFFF & SPI_CLOCK_DIVIDER;
    
    CLEAR_STATUS();
    
    // enable
    SETBIT(LPC_SPI0->CFG, 1);
    
}

uint8_t sendByteToSpi(uint8_t data)
{
    CLEAR_STATUS();
    
    configureSpiSend();
 
    sendSpiEndOfTrame(data);
    
    return 0;
}

void sendBufferToSpi(uint8_t * buffer, uint32_t size)
{
    CLEAR_STATUS();
    
    configureSpiSend();
    
    uint32_t i;
    for (i=0; i < size-1; i++)
    {
        sendSpi(buffer[i]);
    }
    
    sendSpiEndOfTrame(buffer[i]);
    
    // Make sure the last frame sent completely
    while (( LPC_SPI0->STAT & BIT(5)) == 0);

    SETBIT(LPC_SPI0->STAT, 5);

}


uint8_t getByteFromSpi(void)
{
    while ( (LPC_SPI0->STAT & BIT(0))==0);
    return (LPC_SPI0->RXDAT & 0xff);
}

void getBufferFromSpi(uint8_t *buffer, uint32_t size)
{
    CLEAR_STATUS();
        
    // 8 bits of data
    LPC_SPI0->TXCTRL = BITS(24, 7);

    // select slave 0
    CLRBIT(LPC_SPI0->TXCTRL, 16);
    SETBIT(LPC_SPI0->TXCTRL, 17);
    SETBIT(LPC_SPI0->TXCTRL, 18);
    SETBIT(LPC_SPI0->TXCTRL, 19);
    
    // NOT end of transfer
    CLRBIT(LPC_SPI0->TXCTRL, 20);
    // NOT end of frame
    CLRBIT(LPC_SPI0->TXCTRL, 21);
    // NO, rx ignored
    CLRBIT(LPC_SPI0->TXCTRL, 22);
    
    uint32_t i;
    for (i=0; i < size-1; i++)
    {
        sendSpi(0x55);
        buffer[i] = getByteFromSpi();
    }
    
    sendSpiEndOfTrame(0x55);
    buffer[i] = getByteFromSpi();
    
}
