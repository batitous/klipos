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
#include "../include/libs-klipos.h"


void setFsm(Fsm* fsm, Int32 newstate, FsmCall call, FsmCall init)
{
    printf("setFsm: new 0x%x old 0x%x\r\n", newstate, fsm->current);
    
    fsm->current = newstate;
    fsm->call = call;
    fsm->initcall = init;
}

void initFsm(Fsm* fsm, Int32 state, FsmCall call, FsmCall init)
{
    setFsm(fsm, state, call, init);
    
    fsm->init = 1;
    fsm->old = fsm->current;
}

void updateFsm(Fsm* fsm)
{
    if (fsm->init == 1) 
    {
        if (fsm->initcall != 0)
        {
            fsm->initcall();
        }
        
        fsm->init = 0;
    }
    
    if (fsm->call != 0)
    {
        fsm->call();
    }
    
    if (fsm->current != fsm->old)
    {
        fsm->init = 1;
        fsm->old = fsm->current;
    }
}

bool isFsmInState(Fsm* fsm, Int32 state)
{
    if (fsm->current == state)
    {
        return true;
    }
    
    return false;
}

bool isFsmStateInitialized(Fsm* fsm)
{
    if (fsm->init == 0)
    {
        return true;
    }
    
    return false;
}