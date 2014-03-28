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
#ifndef KLIPOS_KERNEL_KQUEUE_H
#define	KLIPOS_KERNEL_KQUEUE_H

#ifdef	__cplusplus
extern "C" {
#endif

/** @brief Queue object */
typedef struct _kqueue_
{
    UInt32      head;   
    UInt32      tail;
    UInt32      size;
    UInt32*     pending;
} KQueue;


/** @brief Initialize a queue
 * 
 * @param queue         Pointer to an allocated queue
 * @param buffer        Queue's buffer
 * @param size          Size of buffer
 */
extern void initKQueue(KQueue* queue, void* buffer, Int32 size);


/** Write a data to the queue
 * 
 * @param queue         Pointer the queue
 * @param data          Data to write
 * @return false if queue full
 */
extern bool writeToKQueue(KQueue* queue, UInt32 data);


/** Read a data from a queue
 * 
 * @param queue         Pointer to the queue
 * @param data          Pointer to the data
 * @return false if queue empty, else true and data stores the queue's data.
 */
extern bool readFromKQueue(KQueue* queue, UInt32* data);



#ifdef	__cplusplus
}
#endif

#endif	/* KQUEUE_H */

