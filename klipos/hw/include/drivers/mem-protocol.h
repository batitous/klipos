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
#ifndef LIB_HW_MEM_PROTOCOL_H
#define LIB_HW_MEM_PROTOCOL_H

#ifdef __cplusplus
extern "C" {
#endif

    
/** Callback when we send data */
typedef void (*MemProtocolSendCallback)(UInt16 address, UInt8 *ptr, UInt32 size);


/** Callback when we receive data */
typedef void (*MemProtocolUpdateCallback)(void);


typedef struct _mem_modules_
{
	UInt16                    id;     /**< Module identifier */
	UInt16                    size;   /**< Size of module */
	UInt8 *                   ptr;	  /**< Address of module */
	MemProtocolUpdateCallback update; /**< Code for update module */
} MemoryModule;


/** @brief Initialize the memory module
 *
 * @param number        Number of modules
 * @param func          Pointer to the sender function
 */
extern void initMemoryModule(UInt32 number, MemProtocolSendCallback send);


/** @brief Add a module to the memory protocol.
 * 
 * @param virtualAddr   Virtual address of your object
 * @param objectAddr    Address of your object
 * @param objectSize    Size of your object
 * @param update        Function for update your object after receiving data
 */
extern void addMemoryModule(UInt16 virtualAddr, UInt8 * objectAddr, UInt32 objectSize, MemProtocolUpdateCallback update);


/** @brief Get a module from an address 
 *
 * @param address       Virtual address of the module
 * @return Pointer to a valid memory module or 0 if error.
 */
extern MemoryModule * getMemoryModuleFromAddress(UInt16 address);


/** @brief Update the memory module.
 * 
 *  memory protocol:
 * 
 * buffer[0] low bits of address
 * buffer[1] high bits of address
 * 
 * if size > 2, then write order: buffer[3] to buffer[size-2] copyied to address
 * else, read order. 
 * 
 * @param buffer        Pointer to a buffer that contains memory data.
 * @param size          Size of buffer.
 */
extern void updateMemoryModule(UInt8 *buffer, UInt8 size);


    
#ifdef __cplusplus
 }
#endif

#endif
