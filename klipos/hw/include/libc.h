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


extern void * memcpy(void *pDestination, const void *pSource, size_t size);

extern void * memset(void *pBuffer, int value, size_t size);

extern int32_t memcmp(const void *pBuffer1, const void *pBuffer2, size_t size);

extern size_t strlen(const char *string);


/* Return 0 if equals
 *  Return >0 if 1st string > 2nd string
 *  Return <0 if 1st string < 2nd string
 */
extern int strncmp(const char* pString1, const char* pString2, size_t count);

extern int strcmp(const char* pString1, const char* pString2);


/* 
 * Copy 'count' byte of pSource into pDestination
 */
char* strncpy(char* pDestination, const char* pSource, size_t count);

extern char * strcpy(char *dest, const char *source);


extern signed int sprintf(char *pStr, const char *pFormat, ...);


#ifdef FIRMWARE_USE_PRINTF

typedef void (*PrintfInterfaceCallback)(uint8_t data); 

extern void setPrintfInterface(PrintfInterfaceCallback callback);

extern void printf(const char *format, ...);

#else
#       define  printf(...)
#endif

#ifdef __cplusplus
 }
#endif

#endif