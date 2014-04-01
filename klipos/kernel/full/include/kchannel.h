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
#ifndef KLIPOS_KERNEL_CHANNEL_H
#define KLIPOS_KERNEL_CHANNEL_H


/** @brief A channel object can be used to communicate between 2 threads
 *  whitout using synchronization or global variables.
 */
typedef struct _kernel_channel_
{
    KThread *   receiver;   /**< the receiver's thread */
    uint32_t      message;    /**< the message */
    bool        empty;      /**< channel empty or not ? */
} KChannel;


/** @brief Initialize a channel object.
 */
extern void initChannel(KChannel *channel);

/** @brief Send a message to a channel object.
 *
 * @param channel   A correct channel object.
 * @param message   A message.
 */
extern void sendMessageToChannel(KChannel * channel, uint32_t message);

/** @brief Wait a message from a channel object.
 *
 * @param channel       A correct channel object.
 * @return Message.
 */
extern uint32_t waitMessageFromChannel(KChannel * channel);

#endif
