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
    uint32_t          time;       /**< time when event posted */
    uint32_t          id;         /**< identifier of event */
    uint32_t          message;    /**< message (optionnal) */
} KEvent;


/** @brief Event callback */
typedef void (*KEventCallback)(KEvent * node);


/** @brief Event manager object */
typedef struct _k_event_manager_
{
    KLink *             next;   /**< next event registered */
    uint32_t              id;     /**< id of event */
    KEventCallback      callback; /**< user callback code */
    uint32_t              data;   /**< specific data for user callback */
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
 * @return true if success
 */
extern bool registerEvent(KEventManager *manager, uint32_t id, KEventCallback user, uint32_t userData);

/** @brief Post an event
 * 
 * @param id
 * @param message
 */
extern void postEvent(uint32_t id, uint32_t message);

/** @brief Post event from an IRQ routine 
 * @param id
 * @param message
 */
extern void postEventFromIrq(uint32_t id, uint32_t message);

#endif
