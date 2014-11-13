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
#ifndef LIB_HW_UTIL_BYTESTREAM_H
#define	LIB_HW_UTIL_BYTESTREAM_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct _bytestream_
{
    uint8_t *       buffer;
    uint8_t *       current;
    uint8_t *       end;
} ByteStream;

extern void write32BitsToBuffer(uint8_t * buffer, uint32_t integer);
extern void write16BitsToBuffer(uint8_t * buffer, uint16_t integer);

extern uint32_t read32BitsFromBuffer(const uint8_t * buffer);
extern uint16_t read16BitsFromBuffer(const uint8_t * buffer);

extern void initByteStream(ByteStream * stream, uint8_t * pBuffer, uint32_t size);
extern void resetByteStream(ByteStream * stream);
extern bool isEndOfStream(ByteStream * stream);
extern uint32_t getByteStreamSize(ByteStream * stream);

extern void write8BitsToStream(ByteStream * stream, uint8_t data);
extern void write16BitsToStream(ByteStream * stream, uint16_t data);
extern void write32BitsToStream(ByteStream * stream, uint32_t data);

extern uint8_t read8BitsFromStream(ByteStream * stream);
extern uint16_t read16BitsFromStream(ByteStream * stream);
extern uint32_t read32BitsFromStream(ByteStream * stream);

extern void writeRawBytesToStream(ByteStream * stream, uint8_t * input, uint32_t size);
extern void readRawBytesFromStream(ByteStream * stream, uint8_t * output, uint32_t size);


#ifdef	__cplusplus
}
#endif

#endif	/* LIB_HW_UTIL_BYTESTREAM_H */

