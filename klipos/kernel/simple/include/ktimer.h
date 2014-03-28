/* 
 * File:   ktime.h
 * Author: baptiste
 *
 * Created on 25 mars 2014, 10:06
 */

#ifndef KTIMER_H
#define	KTIMER_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct _ktimer_
{
    KLink*      next;       /**< pointer to the next timer */
    KLink*      prev;       /**< pointer to the previous timer */
    Int32       remaining;  /**< time remaining before fireup this timer */
    Int32       reload;     /**< time to be reloaded */
    KTask*      task;       /**< timer's task */
} KTimer;

extern void initKernelTimers(void);

extern void initTimer(KTimer* timer, UInt32 delayInUs, KTask* task);


#ifdef	__cplusplus
}
#endif

#endif	/* KTIME_H */

