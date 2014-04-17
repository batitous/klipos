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
#include "i2c-master-common.h"

static uint32_t i2c0_write(uint8_t data);


#define I2C_CNT         65536

static uint32_t private_i2c0_getStat(void)
{
    uint32_t cnt = I2C_CNT;
    while( (I2C_I2CONSET & 0x08) == 0)
    {
       cnt--;
       waitSomeTimeInUs(1);
       if(cnt==0)
       {
           return I2C_TIMEOUT;
       }
    }
    return 0;
}

#define GET_I2C_STATUS()    if( private_i2c0_getStat()!=0){ return I2C_TIMEOUT;}\
                            status = I2C_I2STAT


static uint32_t private_i2c0_send(uint8_t data)
{
    uint32_t cnt = I2C_CNT;
    while( i2c0_write(data) == I2C_BUSY)
    {
        cnt--;
        waitSomeTimeInUs(1);
        if(cnt==0)
        {
            return I2C_TIMEOUT;
        }
    }
    return 0;
}

#define SEND_AND_WAIT(data) if( private_i2c0_send(data)!=0) { return I2C_TIMEOUT;}\
            if( i2c0_wait_after_write() != I2C_OK) return I2C_ERROR_SEND



#define SEND_ACK()			I2C_I2CONSET |= 0x04; /*AA=1*/ I2C_I2CONCLR = 0x08 /*clear SI flag*/
#define SEND_NACK()			I2C_I2CONCLR = 0x04; I2C_I2CONCLR = 0x08   /*clear SI flag*/

static uint32_t i2c0_start(void)
{
//    uint32_t cnt;
    uint32_t result;
    uint8_t status;

    //start
    I2C_I2CONSET = 0x20;

    while(1)
    {
        GET_I2C_STATUS();
        
        //start transmitted
        if((status == 0x08) || (status == 0x10))
        {
            result = I2C_OK;
            break;
        }
        //error
        else if(status != 0xf8)
        {
            result = I2C_ERROR;
            break;
        }
        else
        {
            //clear SI flag
            I2C_I2CONCLR = 0x08;
        }

    }

    //clear start flag
    I2C_I2CONCLR = 0x20;

    return result;
}


static void i2c0_stop(void)
{
    uint32_t cnt = I2C_CNT;

    I2C_I2CONSET |= 0x10;  //STO = 1, set stop flag
    I2C_I2CONCLR = 0x08;   //clear SI flag

    //wait for STOP detected (while STO = 1)
    while((I2C_I2CONSET & 0x10) == 0x10)
    {
        cnt--;
        waitSomeTimeInUs(1);
        if(cnt==0)
        {
            return;
        }
    }
}

static uint32_t i2c0_write(uint8_t data)
{
    //check if I2C Data register can be accessed
    if((I2C_I2CONSET & 0x08) != 0)    //if SI = 1
    {
        /* send data */
        I2C_I2DAT    = data;
        I2C_I2CONCLR = 0x08;       //clear SI flag
        return I2C_OK;
    }
    else
    {
        //data register not ready
        return I2C_BUSY;
    }

}

static uint32_t i2c0_wait_after_write(void)
{
    uint8_t status;

    //DebugPrintf("i2c0_wait_after_write\r\n");
    //wait until data transmitted
    while(1)
    {
        //get new status
        GET_I2C_STATUS();

        /*
         * SLA+W transmitted, ACK received or
         * data byte transmitted, ACK received
         */
        if( (status == 0x18) || (status == 0x28) )
        {
            //data transmitted and ACK received
            return I2C_OK;
        }
        //no relevant status information
        else if(status != 0xf8 )
        {
            //DebugPrintf("i2c0_wait_after_write status = %x\r\n", status);
            return I2C_ERROR;
        }
    }
}


static uint32_t i2c0_read(uint8_t *data)
{
    //check if I2C Data register can be accessed
    if((I2C_I2CONSET & 0x08) != 0)    //SI = 1
    {
        //read data
        *data = I2C_I2DAT;
        return I2C_OK;
    }
    else
    {
        //No data available
        return I2C_EMPTY;
    }
}


uint32_t sendBufferToI2c0(uint8_t addr, uint8_t *buffer, uint32_t len)
{
    uint32_t i;
    //send start condition
    if(i2c0_start()!=I2C_OK)
    {
        //i2c0_stop();
        //DebugPrintf("SendBufferToI2C0.i2c0_start\r\n");
            return I2C_ERROR_START;
    }

    //send address
    SEND_AND_WAIT(addr);

    for(i=0;i<len;i++)
    {
            SEND_AND_WAIT(buffer[i]);
    }

    i2c0_stop();

    //DebugPrintf("SendBufferToI2C0 I2C_OK\r\n");
    return I2C_OK;
}

uint32_t getBufferFromI2c0(uint8_t addr, uint8_t *buffer, uint32_t len)
{
    uint32_t i;
    uint8_t status;
    uint8_t *ptr;

    ptr = buffer;
    if( i2c0_start()!=I2C_OK)
    {
        //DebugPrintf("GetBufferFromI2C0.i2c0_start I2C_ERROR\r\n");
        //i2c0_stop();
        return I2C_ERROR;
    }

    addr = addr|1;
    while( i2c0_write(addr) == I2C_BUSY);

    for(i=0;i<len;i++)
    {
        while(1)
        {
            GET_I2C_STATUS();

            /*
             * SLA+R transmitted, ACK received or
             * SLA+R transmitted, ACK not received
             * data byte received in master mode, ACK transmitted
             */
            if((status == 0x40 ) || (status == 0x48 ) || (status == 0x50 ))
            {
                if(i==len-1)
                {
                        SEND_NACK();
                }
                else
                {
                        SEND_ACK();
                }

                while(i2c0_read(ptr)==I2C_EMPTY);

                ptr++;
                break;

            }
            else if(status != 0xf8 )
            {
                i2c0_stop();
                //DebugPrintf("GetBufferFromI2C0 I2C_ERROR\r\n");
                return I2C_ERROR;
            }

        }//while(1)
    }//for

    i2c0_stop();

    return I2C_OK;
}
