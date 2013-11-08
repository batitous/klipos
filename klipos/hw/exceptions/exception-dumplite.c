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
#include "../../hw/include/libs-default.h"

#include "../include/klist.h"
#include "../include/kthread.h"
#include "../include/kernel.h"

extern volatile KThread * currentTask;

void dumpFaultHandler(UInt32 * stack)
{
    UInt32 r0,r1,r2,r3,r12,lr,pc,psr;
    
    UInt8 string[8];
    UInt32 i;
    
    r0 = stack[0];
    r1 = stack[1];
    r2 = stack[2];
    r3 = stack[3];
    r12 = stack[4];
    lr = stack[5];
    pc = stack[6];
    psr = stack[7];
    

    // print PC LR STACK KERNELTIME
    
    sendByteToUART0('P');
    sendByteToUART0('C');
    sendByteToUART0(':');
    
    PutHexa(string,0,8,0,pc);
    
    for(i=0;i<8;i++)
        sendByteToUART0(string[i]);
    
    
    sendByteToUART0(' ');
    sendByteToUART0('L');
    sendByteToUART0('R');
    sendByteToUART0(':');
    
    PutHexa(string,0,8,0,lr);
    
    for(i=0;i<8;i++)
        sendByteToUART0(string[i]);

    sendByteToUART0(' ');
    sendByteToUART0('S');
    sendByteToUART0('T');
    sendByteToUART0(':');
    
    PutHexa(string,0,8,0,stack);
    
    for(i=0;i<8;i++)
        sendByteToUART0(string[i]);
    
    sendByteToUART0(' ');
    sendByteToUART0('T');
    sendByteToUART0('h');
    sendByteToUART0(':');
    
    PutHexa(string,0,8,0,currentTask);
    
    for(i=0;i<8;i++)
        sendByteToUART0(string[i]);
    
    while(1);
}
