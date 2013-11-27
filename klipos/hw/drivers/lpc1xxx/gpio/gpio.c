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
#include "../../../include/libs-klipos.h"


//----------------------------- get/set/clear pin macro

#ifdef MCU_IS_LPC1311
#       define GPIODIR         gpio->DIR
#       define GPIOGET         gpio->DATA
#       define GPIOSET         SETBIT(gpio->DATA,thepin);
#       define GPIOCLR         CLRBIT(gpio->DATA,thepin);
#       define getGpioPortNumber(pin) 0
#endif

#ifdef MCU_IS_LPC1315
#       define GPIODIR         gpio->DIR[portNumber]
#       define GPIOGET         gpio->PIN[portNumber]
#       define GPIOSET         SETBIT(gpio->SET[portNumber],thepin);
#       define GPIOCLR         SETBIT(gpio->CLR[portNumber],thepin);

UInt32 getGpioPortNumber(GPIO_PIN pin)
{
    if( (pin & 0xFFFF0000) == GPIO_PORT1)
    {
        return 1;
    }
    
    return 0;
}

#endif


#ifdef MCU_IS_LPC17XX
#       define GPIODIR         gpio->FIODIR
#       define GPIOGET         gpio->FIOPIN
#       define GPIOSET         SETBIT(gpio->FIOSET,thepin);
#       define GPIOCLR         SETBIT(gpio->FIOCLR,thepin);
#       define getGpioPortNumber(pin) 0
#endif

//----------------------------- private functions

UInt32 getIRQNumber(UInt32 reg)
{
    UInt32 i;
    
    for (i=0;i<31;i++)
    {
        if ( ((reg >> i)&0x1) != 0)
        {
            return i;
        }
    }
    return 0;
}

LPC_GPIO_TypeDef * getGpioPort(GPIO_PIN pin)
{
    // select io port
    switch(pin & 0xFFFF0000)
    {
        case GPIO_PORT0:
            return LPC_GPIO0;
            break;
        case GPIO_PORT1:
            return LPC_GPIO1;
            break;
            
#ifdef MCU_IS_LPC1311
        case GPIO_PORT2:
            return LPC_GPIO2;
            break;
        case GPIO_PORT3:
            return LPC_GPIO3;
        break;
#endif
        
#ifdef MCU_IS_LPC17XX
        case GPIO_PORT2:
            return LPC_GPIO2;
            break;
        case GPIO_PORT3:
            return LPC_GPIO3;
        break;
        case GPIO_PORT4:
            return LPC_GPIO4;
            break;
#endif
        default:
            return 0;
    }
}

//----------------------------- public functions

void initGpio(void)
{
#ifdef MCU_IS_LPC13XX
    SETBIT(LPC_SYSCON->SYSAHBCLKCTRL,6);
    SETBIT(LPC_SYSCON->SYSAHBCLKCTRL,19);
#endif
}


void setGpioDirection(GPIO_PIN pin, GPIO_DIR dir)
{
    LPC_GPIO_TypeDef * gpio = getGpioPort(pin);
    
#ifdef MCU_IS_LPC1315
    UInt32 portNumber = getGpioPortNumber(pin);
#endif
    
    UInt32 thepin = pin & 0xFFFF;
    
    if(gpio==0)
    {
        return;
    }
    
    if(dir==GPIO_OUT)
    {
        SETBIT(GPIODIR,thepin);
    }
    else
    {
        CLRBIT(GPIODIR,thepin);
    }
    
#ifdef MCU_IS_LPC1311
    //set the fucking FUNC to 1 in SWCLK pin
    if(pin == GPIO0_10)
    {
        SETBIT(LPC_IOCON->SWCLK_PIO0_10,0);
    }
    else if(pin == GPIO0_0)
    {
        SETBIT(LPC_IOCON->RESET_PIO0_0,0);
    }
    else if(pin == GPIO0_11)
    {
        SETBIT(LPC_IOCON->R_PIO0_11,0);
    }
    else if(pin == GPIO1_3)
    {
        SETBIT(LPC_IOCON->SWDIO_PIO1_3,0);
    }
    else if(pin == GPIO1_0)
    {
        SETBIT(LPC_IOCON->R_PIO1_0,0);
    }
    else if(pin == GPIO1_1)
    {
        SETBIT(LPC_IOCON->R_PIO1_1,0);
    }
    else if(pin == GPIO1_2)
    {
        SETBIT(LPC_IOCON->R_PIO1_2,0);
    }
#endif
    
#ifdef MCU_IS_LPC1315
    if(pin == GPIO0_10)
    {
        SETBIT(LPC_IOCON->SWCLK_PIO0_10,0);
    }
    else if(pin == GPIO0_11)
    {
        SETBIT(LPC_IOCON->TDI_PIO0_11,0);
    }
    else if(pin == GPIO0_15)
    {
        SETBIT(LPC_IOCON->SWDIO_PIO0_15,0);
    }
    else if(pin == GPIO0_12)
    {
        SETBIT(LPC_IOCON->TMS_PIO0_12,0);
    }
    else if(pin == GPIO0_13)
    {
        SETBIT(LPC_IOCON->TDO_PIO0_13,0);
    }
    else if(pin == GPIO0_14)
    {
        SETBIT(LPC_IOCON->TRST_PIO0_14,0);
    }
    
#endif
       
#ifdef MCU_IS_LPC17XX

#endif
}

void setGpioValue(GPIO_PIN pin, UInt32 bit)
{
    LPC_GPIO_TypeDef * gpio = getGpioPort(pin);
    
#ifdef MCU_IS_LPC1315
    UInt32 portNumber = getGpioPortNumber(pin);
#endif
    
    UInt32 thepin = pin & 0xFFFF;
    
    if(gpio==0)
    {
        return;
    }
    
    if(bit!=0)
    {
        GPIOSET
    }
    else
    {
        GPIOCLR
    }
}

UInt32 getGpioValue(GPIO_PIN pin)
{
    LPC_GPIO_TypeDef * gpio = getGpioPort(pin);
    
#ifdef MCU_IS_LPC1315
    UInt32 portNumber = getGpioPortNumber(pin);
#endif
    
    UInt32 thepin = pin & 0xFFFF;
    
    if(gpio==0)
    {
        return 0;
    }
    
    return (GPIOGET >> thepin) & 0x1;
}
