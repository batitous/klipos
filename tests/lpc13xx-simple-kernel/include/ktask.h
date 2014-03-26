/* 
 * File:   ktask.h
 * Author: baptiste
 *
 * Created on 24 mars 2014, 19:21
 */

#ifndef KTASK_H
#define	KTASK_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef void (*KTaskCode)(UInt32 dataEvent);

#define QUEUE_SIZE  4

typedef enum _priority_
{
        PRIORIY_IDLE    = 0,
        PRIORITY_LOW    = 1,
        PRIORITY_HIGH   = 254,
        PRIORITY_HIGH_IRQ = 255
} KPriority;

typedef struct _ktask_
{
    KLink *     next;
    KLink *     prev;
    
    KQueue      events;
    UInt32      eventsBuffer[QUEUE_SIZE];
    UInt32      eventId;
    
    KTaskCode   code;
    KPriority   priority;
} KTask;

extern void initTask(KTask* task, KTaskCode c, KPriority prio, UInt32 eventId);

extern bool scheduleTask(void);

extern void executeIdleTask(void);

extern void postEventToTaskWithId(UInt32 id, UInt32 data);

extern void postEventToTask(KTask* task, UInt32 data);

extern void initKernel(void);

#ifdef	__cplusplus
}
#endif

#endif	/* KTASK_H */

