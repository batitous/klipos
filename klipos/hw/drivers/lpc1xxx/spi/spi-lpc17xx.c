/*
 The MIT License (MIT)
 
 Copyright (c) 2013 Baptiste Burles, Christophe Casson, Sylvain Fay-Chatelard
 
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


#define SPI_SCK_PIN		15
#define SPI_MISO_PIN		17
#define SPI_MOSI_PIN		18

#define CPHA    3
#define CPOL    4
#define MSTR    5
#define SPIE	7
#define SPIF	7

void initSpi(void)
{
    // Turn on the power
    SETBIT(LPC_SC->PCONP, 8);

    //clock
    CLRBIT(LPC_SC->PCLKSEL0, 17);
    SETBIT(LPC_SC->PCLKSEL0, 16);

    // setup GPIO
    SETBIT(LPC_GPIO0->FIODIR, SPI_SCK_PIN);
    SETBIT(LPC_GPIO0->FIODIR, SPI_MOSI_PIN);
    CLRBIT(LPC_GPIO0->FIODIR, SPI_MISO_PIN);

    //SCK
    SETBIT(LPC_PINCON->PINSEL0, 30);
    SETBIT(LPC_PINCON->PINSEL0, 31);

    // MISO
    SETBIT(LPC_PINCON->PINSEL1, 2);
    SETBIT(LPC_PINCON->PINSEL1, 3);

    // MOSI
    SETBIT(LPC_PINCON->PINSEL1, 4);
    SETBIT(LPC_PINCON->PINSEL1, 5);

    //set speed
    // sck = PCLK_SPI / value
    // 8 is low speed: ~12,5Mhz
    // 4 = 25 MHz
    // 7 for wifi
    LPC_SPIF->SPCCR = 7;


    SETBIT(LPC_SPIF->SPCR, MSTR);   // 0=slave, 1=master 

    CLRBIT(LPC_SPIF->SPCR, CPHA);   // 0=first clock edge, 1=second clock edge

    CLRBIT(LPC_SPIF->SPCR, CPOL);   // 0=sck active high, 1=sck active low

    CLRBIT(LPC_SPIF->SPCR, SPIE);   // 0=no interrupt, 1=interrupt

        
}



uint8_t sendByteToSpi(uint8_t outgoing)
{
    uint8_t incoming;
    
    LPC_SPIF->SPDR = outgoing;
    
    while (!(LPC_SPIF->SPSR & BIT(SPIF)));
    
    incoming = LPC_SPIF->SPDR;

    return incoming;
}


void sendBufferToSpi(uint8_t * buffer, uint32_t length)
{
    uint32_t i;
    for(i=0; i<length; i++)
    {
        sendByteToSPI(buffer[i]);
    }
}


uint8_t getByteFromSpi(void)
{
    return sendByteToSPI(0x00);
}

void getBufferFromSpi(uint8_t * buffer, uint32_t size)
{
    uint32_t i;
    for (i=0; i<size; i++)
    {
        buffer[i] = getByteFromSPI();
    }
}
