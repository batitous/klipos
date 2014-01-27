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


//----------------------------- public functions

Bool iapWriteBuffer(UInt32 flash_address, UInt32 bufferAddr, UInt32 count)
{
    UInt32 iapParameter[5];
    UInt32 iapResult[5];

    //todo disable irq
    //__disable_irq();
    
    iapParameter[0] = IAP_COPY_RAM_TO_FLASH;
    iapParameter[1] = flash_address;
    iapParameter[2] = (UInt32)bufferAddr;
    iapParameter[3] = count;
    iapParameter[4] = IAP_CCLK;
    iapExecuteCommand(iapParameter,iapResult);

    //todo enable irq
    //__enable_irq();
    
    if(iapResult[0] != IAP_SUCCESS)
    {
        return False;
    }
    return True;
}

Bool iapEraseSector(UInt32 start_sector,UInt32 end_sector)
{
    UInt32 iapParameter[5];
    UInt32 iapResult[5];
    
    iapParameter[0] = IAP_ERASE_SECTOR;
    iapParameter[1] = start_sector;
    iapParameter[2] = end_sector;
    iapParameter[3] = IAP_CCLK;
    iapExecuteCommand(iapParameter,iapResult);
    
    if(iapResult[0] != IAP_SUCCESS)
    {
        return False;
    }
    return True;
}

Bool iapPrepareSector(UInt32 start_sector,UInt32 end_sector)
{
    UInt32 iapParameter[5];
    UInt32 iapResult[5];
    
    iapParameter[0] = IAP_PREPARE_SECTOR_FOR_WRITE;
    iapParameter[1] = start_sector;
    iapParameter[2] = end_sector;
    iapParameter[3] = IAP_CCLK;
    iapExecuteCommand(iapParameter,iapResult);
    
    if(iapResult[0] != IAP_SUCCESS)
    {
        return False;
    }
    return True;
}
