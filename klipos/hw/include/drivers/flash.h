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
#ifndef LIB_HW_FLASH_H
#define LIB_HW_FLASH_H

#ifdef __cplusplus
extern "C" {
#endif



/** Prepare a sector to be writable or erasable 
 * 
 * @param start_sector          Sector start number
 * @param end_sector            Sector end number
 * @return  False if error
 */
extern Bool iapPrepareSector(UInt32 start_sector,UInt32 end_sector);

/** Write data to the specified address in flash memory.
 * 
 * @param flash_address         Memory's address where write the buffer
 * @param buffer                Data's
 * @param count                 Number of bytes to be written
 * @return False if error
 */
extern Bool iapWriteBuffer(UInt32 flash_address, UInt32 * buffer, UInt32 count);

/** Erase a (or multiple) sector of flash memory
 * 
 * @param start_sector          Sector start number 
 * @param end_sector            Sector end number
 * @return False if error
 */
extern Bool iapEraseSector(UInt32 start_sector,UInt32 end_sector);

#ifdef __cplusplus
 }
#endif

#endif
