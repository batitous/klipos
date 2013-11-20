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
#ifndef KLIPOS_KERNEL_IOSTREAM_H
#define KLIPOS_KERNEL_IOSTREAM_H

/** @brief Input/Output Stream object
 */
typedef struct _kernel_io_stream_
{
    KThread *       receiver;   /**< receiver thread */
    UInt8 *         buffer;     /**< input/output buffer */
    UInt16          read;       /**< read index */
    UInt16          write;      /**< write index */
    UInt16          size;       /**< buffer size */
} KIOStream;


/** @brief Create a new IO Stream object.
 *
 * @param size      Size of buffer, MUST BE 8, 16, 32, 64 etc...
 */
extern void initIOStream(KIOStream *stream, UInt8 *buffer, UInt32 size);

/** @brief Write a byte to an IO Stream object.
 *
 * @param stream    IO Stream object.
 * @param data      Byte to write.
 */
extern void writeByteToIOStream(KIOStream *stream, UInt8 data);

extern UInt32 readBufferFromIOStream(KIOStream *stream, UInt8 *buffer, UInt32 len);

/** @brief Get one byte from an IO Stream object.
 *
 * @param stream    IO Stream object.
 * @param data      Pointer to a byte where write the read's byte.
 * @return False if no byte, else True.
 */
extern Bool readByteFromIOStream(KIOStream *stream, UInt8 *data);

/** @brief Wake up a task inside an IRQ.
 *
 * @warning Call this function only in an IRQ !
 *
 * @param stream    IO Stream object.
 */
extern void irqWakeUpTaskFromIOStream(KIOStream *stream);


/** @brief Wait data from an IO Stream object.
 *
 * @param stream    IO Stream object.
 */
extern void waitDataFromIOStream(KIOStream *stream);

/** @brief Is data available from an IO Stream object ?
  * @return True if data available, else False.
  */
extern Bool isDataAvailableFromIOStream(KIOStream *stream);

#endif
