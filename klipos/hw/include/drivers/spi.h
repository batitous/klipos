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
#ifndef LIB_HW_SPI_H
#define LIB_HW_SPI_H

#ifdef __cplusplus
extern "C" {
#endif

// Clock out polarity  / Clock out phase
typedef enum _spi_mode
{
    SPI_MODE0 = 0x00, // cpol = 0 cpha = 0
    SPI_MODE1 = 0x80, // cpol = 0 cpha = 1
    SPI_MODE2 = 0x40, // cpol = 1 cpha = 0
    SPI_MODE3 = 0xC0 // cpol = 1 cpha = 1
} SpiMode;
    
    
extern void initSpi(SpiMode mode);

extern uint8_t sendByteToSpi(uint8_t outgoing);

extern void sendBufferToSpi(uint8_t *buffer, uint32_t size);

extern void sendBufferToSpiAndCloseTransfer(uint8_t * buffer, uint32_t size, bool end);

extern uint8_t getByteFromSpi(void);

extern void getBufferFromSpi(uint8_t *buffer, uint32_t size);


#ifdef __cplusplus
}
#endif

#endif