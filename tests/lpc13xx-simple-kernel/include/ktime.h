/* 
 * File:   ktime.h
 * Author: baptiste
 *
 * Created on 25 mars 2014, 10:06
 */

#ifndef KTIME_H
#define	KTIME_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct _ktime_
{
    KLink*      next;       /**< pointer to the next alarm */
    KLink*      prev;       /**< pointer to the previous alarm*/
    Int32       remaining;  /**< time remaining before alarm */
    Int32       reload;     /**< time to be reloaded */
    KTask*      task;
} KTime;

extern void initKernelTimers(void);

extern void initTimer(KTime* timer, UInt32 delayInUs, KTask* task);


#ifdef	__cplusplus
}
#endif

#endif	/* KTIME_H */

