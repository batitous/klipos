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
#ifndef KLIPOS_KERNEL_KTASK_H
#define	KLIPOS_KERNEL_KTASK_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef void (*KTaskCode)(uint32_t dataEvent);

#define TASK_QUEUE_SIZE  8


/** @brief Task's Priority */
typedef enum _priority_
{
        PRIORIY_IDLE    = 0,
        PRIORITY_LOW    = 1,
        PRIORITY_HIGH   = 254,
        PRIORITY_VERY_HIGH = 255        /**< task can be executed directly in IRQ */
} KPriority;


/** @brief Task object
 *
 */
typedef struct _ktask_
{
    KLink *     next;           /**< next task in the list */
    KLink *     prev;           /**< previous task in the list */
    
    KQueue      events;         /**< queue event of this task */
    uint32_t      eventsBuffer[TASK_QUEUE_SIZE]; /**< event's buffer */
    uint32_t      eventId;        /**< event identifier */
    
    KTaskCode   code;           /**< task's code */
    KPriority   priority;       /**< task's priority */
} KTask;


/** @brief Initialize the simple kernel */
extern void initSimpleKernel(void);


/** @brief Initialize a new task
 * 
 * @param task  The task
 * @param c     Task's code
 * @param prio  Task's priority
 */
extern void initTask(KTask* task, KTaskCode c, KPriority prio);


/** @brief Launch the scheduler and execute any pending task */
extern void scheduleTask(void);


/** @brief Post an event
 * 
 * @param id    Event identifier
 * @param data  Data's event
 */
extern void postEventToTaskWithId(uint32_t id, uint32_t data);


/** Post an event to the specified task
 * 
 * @param task          Task   
 * @param data          Event's data
 * @return false if error (task null, event queue full), else true
 */
extern bool postEventToTask(KTask* task, uint32_t data);


#ifdef	__cplusplus
}
#endif

#endif	/* KTASK_H */

