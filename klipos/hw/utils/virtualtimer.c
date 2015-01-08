/*
 The MIT License (MIT)
 
 Copyright (c) 2015 Baptiste Burles
 
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
#include "../include/libs-klipos.h"


//----------------------------- private variables

//static bool  vTimerInit = false;
//static SList vTimerManager; 


//----------------------------- public functions

void initVirtualTimer(VirtualTimer * timer, VirtualTimerCallback call)
{
/*    if (vTimerInit==false)
    {
        vTimerInit = true;
        initSList(&vTimerManager);
    }
*/    
    timer->tick = 0;
    timer->callback = call;
    
//    insertSNodeToStart(&vTimerManager,(KLink *)timer);
}

void loadVirtualTimer(VirtualTimer * timer, uint32_t load)
{
    timer->tick = load;
}

void updateVirtualTimer(VirtualTimer * t)
{
    if (t->tick != 0)
    {
        t->tick--;

        if (t->tick==0)
        {
            t->callback();
        }
    }
}

/*
void updateVirtualTimers(void)
{
    VirtualTimer * t = (VirtualTimer *)vTimerManager.next;

    while(t!=0)
    {
        if (t->tick != 0)
        {
            t->tick--;
            
            if (t->tick==0)
            {
                t->callback();
            }
        }
        
        t = t->next;
    }
}*/
