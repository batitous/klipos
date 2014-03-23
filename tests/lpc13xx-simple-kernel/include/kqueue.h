/* 
 * File:   kqueue.h
 * Author: baptiste
 *
 * Created on 23 mars 2014, 11:00
 */

#ifndef KQUEUE_H
#define	KQUEUE_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct _kqueue_
{
    UInt32      head;
    UInt32      tail;
    UInt32      size;
    UInt32*     pending;
} KQueue;

extern void initKQueue(KQueue* queue, void* buffer, Int32 size);

extern bool writeToKQueue(KQueue* queue, UInt32 data);

extern bool readFromKQueue(KQueue* queue, UInt32* data);



#ifdef	__cplusplus
}
#endif

#endif	/* KQUEUE_H */

