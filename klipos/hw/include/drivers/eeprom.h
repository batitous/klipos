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
#ifndef LIB_HW_EEPROM_H
#define LIB_HW_EEPROM_H

#ifdef __cplusplus
extern "C" {
#endif

/** /!\ WARNING top 64 bytes of LPC1315's eeprom are reserved !
 * 
 * 
 */

extern bool writeByteToEeprom(uint32_t addr, uint8_t dat);


extern bool writeBufferToEeprom(uint32_t addr, uint8_t* buffer, uint32_t size);


extern bool readByteFromEeprom(uint32_t addr, uint8_t* dat);


extern bool readBufferFromEeprom(uint32_t addr, uint8_t* buffer, uint32_t size);


extern bool eraseEeprom(void);



#ifdef __cplusplus
 }
#endif

#endif
