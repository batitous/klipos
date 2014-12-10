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
#ifndef LIB_HW_IAP_H
#define LIB_HW_IAP_H

#ifdef __cplusplus
extern "C" {
#endif

    
// Function to execute the ROM IAP code of NXP to access flash and eeprom
    

#define IAP_CCLK        KERNEL_CPU_FREQ


typedef enum _iap_command_
{
        IAP_PREPARE_SECTOR_FOR_WRITE	= 50,
        IAP_COPY_RAM_TO_FLASH		= 51,
        IAP_ERASE_SECTOR		= 52,
        IAP_BLANK_CHECK_SECTOR		= 53,
        IAP_READ_PART_ID		= 54,
        IAP_READ_BOOT_VER		= 55,
        IAP_COMPARE			= 56,
        IAP_REINVOKE_ISP		= 57,
        IAP_READ_UID                    = 58, // works on lpc15xx chip
        IAP_WRITE_EEPROM                = 61,
        IAP_READ_EEPROM                 = 62
} IapCommand;


#define IAP_SUCCESS 0

#if defined(MCU_IS_LPC15XX)
#       define IAP_ADDRESS 0x03000205UL
#else
#       define IAP_ADDRESS 0x1FFF1FF1
#endif

/** Execute a low level ROM IAP command
 * 
 * @param param_tab
 * @param result_tab
 */
extern void iapExecuteCommand(uint32_t *param,uint32_t *result);



#ifdef __cplusplus
 }
#endif

#endif
