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

#include "../include/kmemory.h"
#include "../include/klist.h"
#include "../include/kthread.h"
#include "../include/kernel-private.h"
#include "../include/kchannel.h"


void initChannel(KChannel *channel)
{
    channel->empty = true;
    channel->receiver = 0;
}

void sendMessageToChannel(KChannel * channel, UInt32 message)
{
    KThread * th = channel->receiver;
    channel->message = message;
    channel->empty = False;

    if (th!=0)
    {
        channel->receiver = 0;
        setTaskAsReady(th);
    }
}

UInt32 waitMessageFromChannel(KChannel * channel)
{
    // no data, then wait...
    if ( channel->empty == true)
    {
        channel->receiver = (KThread *)currentTask;
        setTaskAsBlocked();
    }

    channel->empty = True;

    return channel->message;
}


