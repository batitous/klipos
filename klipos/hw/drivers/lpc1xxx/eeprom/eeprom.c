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

//--------------------- private functions:

static Bool executeEepromCommand(UInt32 command, UInt32 addr, UInt8 * buffer, UInt32 size)
{
    UInt32 param[5];
    UInt32 result[4];
    
    param[0] = command;
    param[1] = addr;
    param[2] = (UInt32)buffer;
    param[3] = size;
    param[4] = IAP_CCLK;
    iapExecuteCommand(param,result);
    
    if(result[0] != IAP_SUCCESS)
    {
        return False;
    }
    
    return True;
}

//--------------------- public functions:

Bool readByteFromEeprom(UInt32 addr, UInt8* data)
{
    return executeEepromCommand(IAP_READ_EEPROM,addr,data,1);
}

Bool readBufferFromEeprom(UInt32 addr, UInt8* buffer, UInt32 size)
{
    return executeEepromCommand(IAP_READ_EEPROM,addr,buffer,size);
}


Bool writeByteToEeprom(UInt32 addr, UInt8 data)
{
    return executeEepromCommand(IAP_WRITE_EEPROM,addr,&data,1);
}

Bool writeBufferToEeprom(UInt32 addr, UInt8* buffer, UInt32 size)
{
    return executeEepromCommand(IAP_WRITE_EEPROM,addr,buffer,size);
}

Bool eraseEeprom()
{
    return False;
}

