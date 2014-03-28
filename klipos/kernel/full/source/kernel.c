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
#include "../../../hw/include/libs-default.h"

#include "../../common/include/klist.h"
#include "../../common/include/kmemory.h"
#include "../include/kthread.h"
#include "../include/kernel.h"
#include "../include/kernel-private.h"

//-------------------------- private defines

#define IDLE_STACK      96
#define IDLE_CPU        THREAD_CPU_MINIMUM
#define IDLE_PRIORITY   THREAD_PRIORITY_MIN

//-------------------------- private menbers

KList tasksReady;               /**< the ready tasks list */
KList tasksWaiting;             /**< the waiting tasks list */
KList tasksBlocked;             /**< the tasks blocked */

volatile KThread * currentTask; /**< current task in cpu */

static KThread * irqTask;       /**< task requested by an interrupt */
static UInt8 irqPriority;       /**< task priority requested by an interrupt */

static KThread idleThread;    /**< pointer to the idle thread */
static UInt8 idleStack[IDLE_STACK]; /**< idle stack */

volatile UInt32 tickOfKernel;  /**< Number of tick from the beginning */

//-------------------------- private functions

void idleThreadCode(void)
{
    // the idle thread is used in 2 cases:
    // - to start the kernel
    // - when threads aren't available, scheduler select the idle thread

    // when running, the idle thread put the mcu in sleep mode
    
    while(1)
    {
        setMcuToDefaultSleep();
    }
}

void kernelScheduler(void)
{
    // we are in kernel mode !
    tickOfKernel++;
    
    currentTask->quantum--;

#ifdef KERNEL_USE_DEBUG
    currentTask->cpuUsage++;

    UInt32 size = currentTask->stack - currentTask->stackBegin;
    if( size > currentTask->stackUsage)
    {
        currentTask->stackUsage = size;
    }
#endif
    
    if( currentTask->quantum == 0)
    {
        currentTask->quantum = currentTask->cpuRequest;

        currentTask = (KThread *)currentTask->next;

        if(currentTask == &idleThread || currentTask == (KThread *)&tasksReady )
        {
            currentTask = (KThread *)(tasksReady.next);
        }

    }
    
    if( irqPriority != 0)
    {
        // an irq request to load a task
        currentTask = irqTask;
        irqPriority = 0;
    }


}


// ca bourine mais ca casse le temps reel
//#define insertThreadToReady(th) insertKNodeToEnd(&readyTasks, (KNode *)th)


void insertThreadToReady( KThread * th)
{
    KThread * temp = (KThread *)tasksReady.next;
    KThread * p;

    while( temp != (KThread *)&tasksReady )
    {
        if( th->priority >= temp->priority )
        {
            break;
        }
        temp = temp->next;
    }

    p = temp->prev;
    th->next = temp;
    th->prev = p;

    p->next = th;
    temp->prev = th;

}

void kernelService2(KThread * thread)
{
    // we are in kernel mode but not in the kernel scheduler !

    // we have to wakeup a thread:
    // - move task to ready list
    // - if new task has a greater priority than the current, then switch

    if(thread->isReady==False)
    {
        thread->isReady = True;
        removeKNode((KNode *)thread);
        insertThreadToReady((KThread *)thread);
        
        // reload the quantum of the new task to be sure that the new task has cpu
        thread->quantum = thread->cpuRequest;

        if( thread->priority >= currentTask->priority)
        {
            // we can have an irq task request before kernel service 2 :
            // - if thread priority greather than an irq priority, then cancel the irq task request
            if( thread->priority >= irqPriority)
            {
                irqPriority = 0;
                currentTask = thread;
            }
        }
    }
}

void kernelService3(KList * list)
{
    // we are in kernel mode but not in the kernel scheduler !

    // we have to select a new task : the currentTask is removed from the ready task list

    KThread * thread = (KThread *) currentTask;

    // update currentTask
    currentTask = (KThread *)currentTask->next;
    if( currentTask == (KThread *)&tasksReady)
    {
        currentTask = (KThread *)(tasksReady.next);
    }

    // insert thread in the correct list
    if(thread->isReady==True)
    {
        thread->isReady = False;
        
        removeKNode((KNode *)thread);
        insertKNodeToEnd(list,(KNode *)thread);
    }
}

void kernelSetTaskAsReady(KThread * thread )
{
    // we are in kernel mode and just before the kernel scheduler !

    // call by the timer management:
    // - move task to ready list
    // - if task has greather priority than the current, then switch

    if(thread->isReady==False)
    {
        thread->isReady = True;
        
        removeKNode((KNode *)thread);
        insertThreadToReady(thread);
    }
    
    // reload task quantum
    thread->quantum = thread->cpuRequest;

    if(thread->priority >= currentTask->priority)
    {
        // we can have an irq task request before the kernel scheduler:
        // - if thread priority greather than an irq priority, then cancel the irq task request
        if( thread->priority >= irqPriority)
        {
            irqPriority = 0;

            // we set +1 because kernel scheduler decrement one tick:
            thread->quantum = thread->quantum +1;
            currentTask = thread;
        }
    }
}

void irqSetTaskAsReady( KThread * thread)
{
    // we are inside an driver irq !

    // the driver irq wake up a task:
    // - move task to ready list
    // - if task has greather priority than the current, then switch
    // we cant change task in the irq, we have to wait the next kernel scheduler tick

    if(thread->isReady==False)
    {
        thread->isReady = True;
        
        removeKNode((KNode *)thread);
        insertThreadToReady(thread);
        
        // reload thread quantum to be sure that the new task has enough cpu time
        thread->quantum = thread->cpuRequest;

        // check the new thread priority against the current task
        if( thread->priority >= currentTask->priority && thread->priority >= irqPriority)
        {
            irqTask = thread;
            irqPriority = thread->priority;
        }
    }
    
}

/* called by the 'Software Interrupt' processor instruction */
void SVC_Handler(void) __attribute__( ( naked ) );
void SVC_Handler(void)
{
    // modification of EXC_RETURN value in a interrupt (ARM datasheet page 119)

    // the Software Interrupt is used to call various kernel service

    __asm __volatile__(

    /* first, we retrieve the correct stack : the thread stack or the kernel stack */

    "tst    lr, #4\r\n"         /* test bit 3 of link register */
    "ite    eq\r\n"             /* begin a if block (next 2 instructions are the if-else) */
    "mrseq  r0,MSP\r\n"         /* if egual, load the Main Stack Pointer into r0 */
    "mrsne  r0,PSP\r\n"         /* else load the Process Stack Pointer into r0 */

    /* second, we save the software interrupt number in r1 */

    "ldr    r1, [r0,#24]\r\n"   /* get the pc address from the stack */
    "ldrb   r1, [r1,#-2]\r\n"   /* and then get the svc number from the pc address */

    /* and we save software interrupt parameter in r0 */

    "ldr    r0, [r0,#0]\r\n"     /* get the svc parameter */

    /* and now, we can run the kernel service ! */

    "cmp    r1,#2\r\n"
    "bne    svc_3\r\n"          /* if r1 is not egual to 2, then go to svc_3 */

    /*** service 2 : wake up a task from the waiting list */

    "mrs    r2, psp\r\n"        /* get process stack pointer */
    "stmdb  r2!, {r4-r11}\r\n"  /* save all registers at r2 address */

    "ldr    r3, currentTask1\r\n"/* load currentTask1 label into r3 */
    "ldr    r12, [r3]\r\n"      /* load address of currentTask into r12 */
    "str    r2, [r12, #8]\r\n"  /* save r2 at currentTask+8 : save thread stack pointer */

    "cpsid  i\r\n"               /* disable interrupt */        
            
    "push   {lr}\r\n"           /* we need to backup the link register because the C code modify the lr */
    "bl     kernelService2\r\n"    /* select the next task */

    "cpsie  i\r\n"               /* enable interrupt */            
            
    "ldr    r3, currentTask1\r\n"  /* load currentTask1 label into r3 */
    "ldr    r1, [r3]\r\n"       /* load address of currentTask into r1 */
    "ldr    r0, [r1, #8]\r\n"   /* load currentTask+8 into r0 ( equivalent to currentTask->stack in C ) */

    "ldmia  r0!, {r4-r11}\r\n"  /* load register from r0 address into the new stack */
    "msr    psp, r0\r\n"        /* set the process stack pointer to the new stack */

    "pop    {pc}\r\n"             /* exit kernel and run the next thread */

    "svc_3:\r\n"
    "cmp    r1,#3\r\n"
    "bne    svc_1\r\n"        /* if r1 is not egual to 3, then go to svc_1 */

    /*** service 3 : set current task in the waiting list */

    "mrs    r2, psp\r\n"        /* get process stack pointer */
    "stmdb  r2!, {r4-r11}\r\n"  /* save all registers at r2 address */

    "ldr    r3, currentTask1\r\n"/* load currentTask1 label into r3 */
    "ldr    r12, [r3]\r\n"      /* load address of currentTask into r12 */
    "str    r2, [r12, #8]\r\n"  /* save r2 at currentTask+8 : save thread stack pointer */

    "cpsid  i\r\n"               /* disable interrupt */        
            
    "push   {lr}\r\n"           /* we need to backup the link register because the C code modify the lr */
    "bl     kernelService3\r\n" /* set the next task */

    "cpsie  i\r\n"               /* enable interrupt */           
            
    "ldr    r3, currentTask1\r\n"  /* load currentTask1 label into r3 */
    "ldr    r1, [r3]\r\n"       /* load address of currentTask into r1 */
    "ldr    r0, [r1, #8]\r\n"   /* load nextTask+8 into r0 ( equivalent to currentTask->stack in C ) */

    "ldmia  r0!, {r4-r11}\r\n"  /* load register from r0 address into the new stack */
    "msr    psp, r0\r\n"        /* set the process stack pointer to the new stack */

    "pop    {pc}\r\n"           /* exit kernel and run the selected thread */

    "svc_1:\r\n"
    "cmp    r1,#1\r\n"
    "bne    svc_end\r\n"        /* if r1 is not egual to 1, then exit kernel */

    /*** service 1 : start kernel */

    "ldr    r3, currentTask1\r\n"/* load address of label currentTask1 into r3 */
    "ldr    r1, [r3]\r\n"       /* load address of currentTask into r1 */
    "ldr    r0, [r1, #8]\r\n"   /* load currentTask+8 into r0 ( equivalent to currentTask->stack in C ) */

    "ldmia  r0!, {r4-r11}\r\n"  /* restore the thread stack */
    "msr    psp, r0\r\n"        /* set the process stack pointer with r0 */

    "orr    lr, lr, #4\r\n"     /* force link register to use the process stack pointer */
    "bx     lr\r\n"             /* exit the kernel : first task is created in thread mode ! */

    "svc_end:\r\n"
    "bx     lr\r\n"             /* exit kernel */

    ".align 2\r\n"              /* align next label: cortex don't love data unaligned */
    "currentTask1: .word currentTask" /* currentTask1 'store' the currentTask pointer */
    );

}

void SysTick_Handler(void)
{
    // set PendSV bit to 1 : SysTick Interrupt is executed in the low priority PendSV_Handler Interrupt
    SCB->ICSR = 0x10000000;
}

/* called by the processor after the others interrupts */
void PendSV_Handler(void) __attribute__( ( naked ) );
void PendSV_Handler(void)
{
    // code comes from context switcher (ARM datasheet page 120)
    // this code switch thread on the processor.

    // this interrupt has a low priority :
    // we are sure that we don't switch in middle of an interrupt

     __asm __volatile__ (

               
        "mrs    r2, psp\r\n"        /* get process stack pointer */
        "stmdb  r2!, {r4-r11}\r\n"  /* save all registers at r2 address */

        "ldr    r3, currentTask2\r\n"/* load currentTask2 label into r3 */
        "ldr    r1, [r3]\r\n"        /* load address of currentTask into r1 */
        "str    r2, [r1, #8]\r\n"    /* save r2 at currentTask+8 : save thread stack pointer */

        "cpsid  i\r\n"               /* disable interrupt */
        "push   {lr}\r\n"            /* we need to backup the link register because the C code modify the lr */
        "bl     manageKTimer\r\n"    /* manage timer and alarm */
        "bl     kernelScheduler\r\n" /* and switch task */
        "cpsie  i\r\n"               /* enable interrupt */    
        
        "ldr    r3, currentTask2\r\n"/* load currentTask2 label into r3 */
        "ldr    r1, [r3]\r\n"        /* load address of currentTask into r1 */
        "ldr    r0, [r1, #8]\r\n"    /* load currentTask+8 into r0 ( equivalent to currentTask->stack in C ) */

        "ldmia  r0!, {r4-r11}\r\n"   /* load register from r0 address into the new stack */
        "msr    psp, r0\r\n"         /* set the process stack pointer to the new stack */
    
        "pop    {pc}\r\n"           /* exit kernel and run the selected thread */
        ".align 2\r\n"              /* align next label: cortex don't love data unaligned */
        "currentTask2: .word currentTask" /* currentTask2 is a label that store the currentTask pointer */
    );
}


//-------------------------- public functions

void initThread( KThread *thread, void (*userCode)(void), UInt8 *stack, UInt32 stackSize, UInt8 cpuTime, UInt8 priority)
{
    thread->stack = (UInt32 *)stack;
    
#ifdef KERNEL_USE_DEBUG
    thread->stackBegin = thread->stack;
#endif
    
    // the cortex cpu has a "descendant stack", the stack begins at the "top address" :
    thread->stack = thread->stack + (stackSize>>2) -1;

    // cortex-m3 save automatically in that order :
    // xpsr
    // pc (address of code)
    // lr (return address)
    // r12 r3 r2 r1 r0
    // we need to backup :
    // r11 r10 r9 r8 r7 r6 r5 r4

    // to create the thread stack, we set only xpsr, pc and lr.

    //todo when thread exit, set lr to something ????

    *thread->stack = (UInt32)0x01000000; // xpsr register : T bit set to 1 for thumb mode
    thread->stack--;
    *thread->stack = (UInt32)userCode; // Thread code
    thread->stack--;
    *thread->stack = 0 ; // Link Register
    thread->stack -= 5;  //R12 R3 R2 R1
    *thread->stack = 0 ; //R0 paramerer
    thread->stack -= 8;  //R11 R10 R9 R8 R7 R6 R5 R4

    thread->cpuRequest = cpuTime;
    thread->quantum = thread->cpuRequest;
    thread->waiting = 0;
    thread->priority = priority;
    thread->isReady = True;
    
#ifdef KERNEL_USE_DEBUG
    thread->cpuUsage = 0;
    thread->stackUsage = 0;
#endif
    
    insertThreadToReady(thread);
}

void initKernel(void)
{
    initKList(&tasksReady);
    initKList(&tasksWaiting);
    initKList(&tasksBlocked);
    initKAlarm();

    initThread(&idleThread, &idleThreadCode, idleStack, IDLE_STACK, IDLE_CPU, IDLE_PRIORITY);
    
}

void startKernel(void)
{
    // unit : 10us
    UInt32 tick = 10;

    // set Software / PendSV interrupt the same and lowest priority
    NVIC_SetPriority(SVCall_IRQn, 31);
    NVIC_SetPriority(PendSV_IRQn, 31);

    irqPriority = 0;
    irqTask = 0;
    currentTask = &idleThread;

    // init system tick timer :
    SysTick_Config( (KERNEL_CPU_FREQ/100)*tick -1 ) ;

    tickOfKernel = 0;
    
    // call the software interrupt 1
    __asm __volatile__ (
        "svc 1" /* cette putin d'instruction ne prend que des constantes en paramétres */
    );

    // when kernel start, we never reach this line !
    while(1)
    {
    }
}

void setTaskAsReady(KThread * thread)
{
    // we are in thread mode

    // call the software interrupt 2
    __asm __volatile__ (
        "mov r0, %0\r\n"
        "svc 2"
        : : "r" ((UInt32)thread) );
}

void setTaskAsWaiting(void)
{
    // we are in thread mode

    // call the software interrupt 3
    __asm __volatile__ (
        "mov r0, %0\r\n"
        "svc 3"
        : : "r" ((UInt32)&tasksWaiting) );
}


void setTaskAsBlocked(void)
{
    // we are in thread mode

    // call the software interrupt 3
    __asm __volatile__ (
        "mov r0, %0\r\n"
        "svc 3"
        : : "r" ((UInt32)&tasksBlocked) );
}

UInt32 getCurrentTimeOfKernel(void)
{
    return tickOfKernel;
}

void irqWakeUpTaskFromIOStream(KIOStream *stream)
{
    KThread * th = stream->receiver;
    
    if(th!=0)
    {
        // a task is waiting, wakeup this task !
        stream->receiver = 0;
        irqSetTaskAsReady(th);
    }
}

void waitDataFromIOStream(KIOStream *stream)
{
    if( stream->read==stream->write)
    {
        stream->receiver = (KThread *)currentTask;
        setTaskAsBlocked();
    }
}
