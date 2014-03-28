Klipos
======

An embedded framework and operating system for ARM Cortex-M microcontroller.


Microcontrollers supported
==========================

The framework has been tested on this micro-controller :
- LPC1311
- LPC1315
- LPC1317
- LPC1343
- LPC1347
- LPC800


Firmware configuration
======================

You can choose driver & functionnality of your firmware by the Makefile.options



Multitasking
============

You can choose 3 options for your application :

- No multitasking :
Your application manages everything (IRQ, mainloop, ...)


- Cooperative multitasking : 
Each task must respect the 'Run-To-Completion' model.
One memory stack for all the task.
Event-driven and tickless kernel.


- Preemptive multitasking :
Each task has his own memory stack.
Scheduler tick at 100 us (and all time has a precision of 100 us).



License
=======

Most of the code are under the MIT license (or BSD equivalent).
