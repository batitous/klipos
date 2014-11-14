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
#endif

#ifdef MCU_IS_LPC1315
#       define GPIODIR         gpio->DIR[portNumber]
#       define GPIOGET         gpio->PIN[portNumber]
#       define GPIOSET         SETBIT(gpio->SET[portNumber],thepin);
#       define GPIOCLR         SETBIT(gpio->CLR[portNumber],thepin);
#       define GPIOTOGGLE      SETBIT(gpio->NOT[portNumber],thepin);
#endif


#ifdef MCU_IS_LPC17XX
#       define GPIODIR         gpio->FIODIR
#       define GPIOGET         gpio->FIOPIN
#       define GPIOSET         SETBIT(gpio->FIOSET,thepin);
#       define GPIOCLR         SETBIT(gpio->FIOCLR,thepin);
#endif

//----------------------------- private functions

uint32_t getIRQNumber(uint32_t reg)
{
    uint32_t i;
    
    for (i=0;i<31;i++)
    {
        if ( ((reg >> i)&0x1) != 0)
        {
            return i;
        }
    }
    return 0;
}

static const LPC_GPIO_TypeDef * lpcGpioArray[] =
{
    LPC_GPIO0,
    LPC_GPIO1
#ifdef MCU_IS_LPC1311
            ,
    LPC_GPIO2,
    LPC_GPIO3
#endif

#ifdef MCU_IS_LPC17XX
             ,
    LPC_GPIO2,
    LPC_GPIO3,
    LPC_GPIO4
#endif
};

#define GET_LPC_GPIO_PORT(pin)      (LPC_GPIO_TypeDef *)lpcGpioArray[((pin) & 0xFFFF0000)>>16]

//----------------------------- public functions

void initGpio(void)
{
#ifdef MCU_IS_LPC13XX
    SETBIT(LPC_SYSCON->SYSAHBCLKCTRL,6);
#endif
    
#ifdef MCU_IS_LPC1315
    SETBIT(LPC_SYSCON->SYSAHBCLKCTRL,19);
    SETBIT(LPC_SYSCON->SYSAHBCLKCTRL,23);
    SETBIT(LPC_SYSCON->SYSAHBCLKCTRL,24);
#endif
}

LPC_GPIO_TypeDef * getLpcGpio(uint32_t pin)
{
    return GET_LPC_GPIO_PORT(pin);
}

void setGpioDirection(GPIO_PIN pin, GPIO_DIR dir)
{
    LPC_GPIO_TypeDef * gpio = GET_LPC_GPIO_PORT(pin);
    
#ifdef MCU_IS_LPC1315
    uint32_t portNumber = GET_GPIO_PORT_NUMBER(pin);
#endif
    
    uint32_t thepin = pin & 0xFFFF;
        
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

void setGpioValue(GPIO_PIN pin, uint32_t bit)
{
    LPC_GPIO_TypeDef * gpio = GET_LPC_GPIO_PORT(pin);
    
#ifdef MCU_IS_LPC1315
    uint32_t portNumber = GET_GPIO_PORT_NUMBER(pin);
#endif
    
    uint32_t thepin = pin & 0xFFFF;
    
    if(bit!=0)
    {
        GPIOSET
    }
    else
    {
        GPIOCLR
    }
}

uint32_t getGpioValue(GPIO_PIN pin)
{
    LPC_GPIO_TypeDef * gpio = GET_LPC_GPIO_PORT(pin);
    
#ifdef MCU_IS_LPC1315
    uint32_t portNumber = GET_GPIO_PORT_NUMBER(pin);
#endif
    
    uint32_t thepin = pin & 0xFFFF;
        
    return (GPIOGET >> thepin) & 0x1;
}

#ifdef MCU_IS_LPC1315

void toggleGpio(GPIO_PIN pin)
{
    LPC_GPIO_TypeDef * gpio = GET_LPC_GPIO_PORT(pin);

    uint32_t portNumber = GET_GPIO_PORT_NUMBER(pin);

    
    uint32_t thepin = pin & 0xFFFF;
    
    GPIOTOGGLE
}

#endif
