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
#ifndef KLIPOS_KERNEL_EVENT_H
#define KLIPOS_KERNEL_EVENT_H


/** @brief An event */
typedef struct _k_event_
{
    UInt32          time;       /**< time when event posted */
    UInt32          id;         /**< identifier of event */
    UInt32          message;    /**< message (optionnal) */
} KEvent;


/** @brief Event callback */
typedef void (*KEventCallback)(KEvent * node);


/** @brief Event manager object */
typedef struct _k_event_manager_
{
    KLink *             next;   /**< next event registered */
    UInt32              id;     /**< id of event */
    KEventCallback      callback; /**< user callback code */
    UInt32              data;   /**< specific data for user callback */
} KEventManager;


// don't use id event with bit > 0x10000, it's system reserved !


#define KEVENT_GPIO_MASK        0x80000000      /**< gpio interrupt event */
#define KEVENT_ALARM_MASK       0x40000000      /**< alarm event */


/** @brief Initialize the event manager 
 */
extern void initEventManager(void);

/** @brief Register a event
 * @param id
 * @param user
 * @param userData
 * @return True if success
 */
extern Bool registerEvent(KEventManager *manager, UInt32 id, KEventCallback user, UInt32 userData);

/** @brief Post an event
 * 
 * @param id
 * @param message
 */
extern void postEvent(UInt32 id, UInt32 message);

/** @brief Post event from an IRQ routine 
 * @param id
 * @param message
 */
extern void postEventFromIrq(UInt32 id, UInt32 message);

#endif
