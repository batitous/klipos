/*
 The MIT License (MIT)
 
 Copyright (c) 2014 Baptiste Burles
 
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
#include "../include/libs-klipos.h"

void write32bitsToBuffer(uint8_t * buffer, uint32_t integer)
{
    buffer[0] = (uint8_t)(integer & 0xFF);
    buffer[1] = (uint8_t)((integer>>8UL) & 0xFF);
    buffer[2] = (uint8_t)((integer>>16UL) & 0xFF);
    buffer[3] = (uint8_t)((integer>>24UL) & 0xFF);
}

uint32_t read32bitsFromBuffer(const uint8_t * buffer)
{
    uint32_t integer;
    uint32_t temp;
    
    temp = buffer[3];
    integer = temp << 24UL;
    
    temp = buffer[2];
    integer = (temp << 16UL) | integer;
    
    temp = buffer[1];
    integer = (temp << 8UL) | integer;
    
    temp = buffer[0];
    integer = (temp) | integer;
    
    return integer;
}

void write16bitsToBuffer(uint8_t * buffer, uint16_t integer)
{
    buffer[0] = (uint8_t)(integer);
    buffer[1] = (integer>>8UL);
}

uint16_t read16bitsFromBuffer(const uint8_t * buffer)
{
    uint16_t integer = (buffer[1]<<8UL)| (buffer[0]);
    
    return integer;
}

void initByteStream(ByteStream * stream, uint8_t * pBuffer, uint32_t size)
{
    stream->buffer = pBuffer;
    stream->current = pBuffer;
    stream->end = pBuffer + size;
}

void resetByteStream(ByteStream * stream)
{
    stream->current = stream->buffer;
}

bool isEndOfStream(ByteStream * stream)
{
    if (stream->current == stream->end)
    {
        return true;
    }
    
    return false;
}

uint32_t getByteStreamSize(ByteStream * stream)
{
    return (uint32_t)(stream->current - stream->buffer);
}

void write8BitsToStream(ByteStream * stream, uint8_t data)
{
    *stream->current = data;
    stream->current++;
}

void write16BitsToStream(ByteStream * stream, uint16_t data)
{
    write16bitsToBuffer(stream->current, data);
    stream->current += 2;
}

void write32BitsToStream(ByteStream * stream, uint32_t data)
{
    write32bitsToBuffer(stream->current, data);
    stream->current += 4;
}

void writeRawBytesToStream(ByteStream * stream, uint8_t * input, uint32_t size)
{
    memcpy(stream->current, input,size);
    stream->current += size;
}

uint8_t read8BitsFromStream(ByteStream * stream)
{
    uint8_t data = *stream->current;
    stream->current++;

    return data;
}

uint16_t read16BitsFromStream(ByteStream * stream)
{
    uint16_t integer = read16bitsFromBuffer(stream->current);
    
    stream->current +=2;
    return integer;
}

uint32_t read32BitsFromStream(ByteStream * stream)
{
    uint32_t integer = read32bitsFromBuffer(stream->current);
    
    stream->current +=4;
    return integer;
}

void readRawBytesFromStream(ByteStream * stream, uint8_t * output, uint32_t size)
{
    memcpy(output, stream->current,size);
    stream->current += size;
}
