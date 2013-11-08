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
#ifndef LIBS_HW_LIBC_H
#define LIBS_HW_LIBC_H

#ifdef __cplusplus
extern "C" {
#endif

// libc function


extern void * memcpy(void *pDestination, const void *pSource, UInt32 size);

extern void * memset(void *pBuffer, int value, UInt32 size);

extern Int32 memcmp(const void *pBuffer1, const void *pBuffer2, UInt32 size);

extern UInt32 strlen(const Int8 *string);


/* Return 0 if equals
 *  Return >0 if 1st string > 2nd string
 *  Return <0 if 1st string < 2nd string
 */
extern Int32 strncmp(const Int8 *pString1, const Int8 *pString2, UInt32 count);

extern Int32 strcmp(const Int8 *pString1, const Int8 *pString2);


/* 
 * Copy 'count' byte of pSource into pDestination
 */
extern Int8 * strncpy(Int8 *pDestination, const Int8 *pSource, UInt32 count);

extern Int8 * strcpy(Int8 *pDestination, const Int8 *pSource);


extern signed int sprintf(char *pStr, const char *pFormat, ...);


#ifdef __cplusplus
 }
#endif

#endif