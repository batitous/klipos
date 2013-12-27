/**************************************************************************/
/*!
    @file     uart.c
    @author   K. Townsend

    @section LICENSE

    Software License Agreement (BSD License)

    Copyright (c) 2013, K. Townsend (microBuilder.eu)
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
    1. Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
    3. Neither the name of the copyright holders nor the
    names of its contributors may be used to endorse or promote products
    derived from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ''AS IS'' AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
/**************************************************************************/

#include "../../include/libs-klipos.h"


#define UART_ENABLE          (1 << 0)
#define UART_DATA_LENGTH_8   (1 << 2)
#define UART_PARITY_NONE     (0 << 4)
#define UART_STOP_BIT_1      (0 << 6)

/* Status bits */
#define UART_STATUS_RXRDY    (1 << 0)
#define UART_STATUS_RXIDLE   (1 << 1)
#define UART_STATUS_TXRDY    (1 << 2)
#define UART_STATUS_TXIDLE   (1 << 3)
#define UART_STATUS_CTSDEL   (1 << 5)
#define UART_STATUS_RXBRKDEL (1 << 11)

void initUart0(void)
{
    uint32_t baudRate = 115200;
    uint32_t clk;
    const uint32_t UARTCLKDIV=1;

    /* Setup the clock and reset UART0 */
    LPC_SYSCON->UARTCLKDIV = UARTCLKDIV;
    NVIC_DisableIRQ(UART0_IRQn);
    LPC_SYSCON->SYSAHBCLKCTRL |=  (1 << 14);
    LPC_SYSCON->PRESETCTRL    &= ~(1 << 3);
    LPC_SYSCON->PRESETCTRL    |=  (1 << 3);

    /* Configure UART0 */
    clk = __MAIN_CLOCK/UARTCLKDIV;
    LPC_USART0->CFG = UART_DATA_LENGTH_8 | UART_PARITY_NONE | UART_STOP_BIT_1;
    LPC_USART0->BRG = clk / 16 / baudRate - 1;
    LPC_SYSCON->UARTFRGDIV = 0xFF;
    LPC_SYSCON->UARTFRGMULT = (((clk / 16) * (LPC_SYSCON->UARTFRGDIV + 1)) /
      (baudRate * (LPC_USART0->BRG + 1))) - (LPC_SYSCON->UARTFRGDIV + 1);

    /* Clear the status bits */
    LPC_USART0->STAT = UART_STATUS_CTSDEL | UART_STATUS_RXBRKDEL;

    /* Enable UART0 interrupt */
    NVIC_EnableIRQ(UART0_IRQn);

    /* Enable UART0 */
    LPC_USART0->CFG |= UART_ENABLE;
}

void sendByteToUart0(UInt8 data)
{
    while (!(LPC_USART0->STAT & UART_STATUS_TXRDY));
    LPC_USART0->TXDATA = data;
}

void sendBufferToUart0(UInt8* buffer, UInt32 length)
{
    while (length != 0)
    {
        sendByteToUart0(*buffer);
        buffer++;
        length--;
    }
}