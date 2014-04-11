/***********************************************************************
* $Id:: mw_usbd_rom_api.h 197 2011-06-12 20:22:41Z usb06052                   $
*
* Project: USB device ROM Stack
*
* Description:
*     ROM API Module definitions.
*
***********************************************************************
*   Copyright(C) 2011, NXP Semiconductor
*   All rights reserved.
*
* Software that is described herein is for illustrative purposes only
* which provides customers with programming information regarding the
* products. This software is supplied "AS IS" without any warranties.
* NXP Semiconductors assumes no responsibility or liability for the
* use of the software, conveys no license or title under any patent,
* copyright, or mask work right to the product. NXP Semiconductors
* reserves the right to make changes in the software without
* notification. NXP Semiconductors also make no representation or
* warranty that such application will be suitable for the specified
* use without further testing or modification.
**********************************************************************/
#ifndef __MW_USBD_ROM_API_H
#define __MW_USBD_ROM_API_H

#ifdef __cplusplus
extern "C" {
#endif

/** \file
 *  \brief ROM API for USB device stack.
 *
 *  Definition of functions exported by ROM based USB device stack.
 *
 */

#include "error.h"
#include "mw_usbd.h"
#include "mw_usbd_hw.h"
#include "mw_usbd_desc.h"
#include "mw_usbd_core.h"
#include "mw_usbd_mscuser.h"
#include "mw_usbd_dfuuser.h"
#include "mw_usbd_hiduser.h"
#include "mw_usbd_cdcuser.h"

/** \brief Main USBD API functions structure.
 *  \ingroup Group_USBD
 *
 *  This structure contains pointer to various USB Device stack's sub-module 
 *  function tables. This structure is used as main entry point to access
 *  various methods (grouped in sub-modules) exposed by ROM based USB device 
 *  stack.
 *
 */
typedef struct USBD_API 
{
  const USBD_HW_API_T* hw; /**< Pointer to function table which exposes functions 
                           which interact directly with USB device stack's core 
                           layer.*/
  const USBD_CORE_API_T* core; /**< Pointer to function table which exposes functions 
                           which interact directly with USB device controller 
                           hardware.*/
  const USBD_MSC_API_T* msc; /**< Pointer to function table which exposes functions 
                           provided by MSC function driver module.
                           */
  const USBD_DFU_API_T* dfu; /**< Pointer to function table which exposes functions 
                           provided by DFU function driver module.
                           */
  const USBD_HID_API_T* hid; /**< Pointer to function table which exposes functions 
                           provided by HID function driver module.
                           */
  const USBD_CDC_API_T* cdc; /**< Pointer to function table which exposes functions 
                           provided by CDC-ACM function driver module.
                           */
  const uint32_t* reserved6; /**< Reserved for future function driver module.
                           */
  const uint32_t version; /**< Version identifier of USB ROM stack. The version is
                          defined as 0x0CHDMhCC where each nibble represnts version 
                          number of the corresponding component.
                          CC -  7:0  - 8bit core version number
                           h - 11:8  - 4bit hardware interface version number
                           M - 15:12 - 4bit MSC class module version number
                           D - 19:16 - 4bit DFU class module version number
                           H - 23:20 - 4bit HID class module version number
                           C - 27:24 - 4bit CDC class module version number
                           H - 31:28 - 4bit reserved 
                           */

} USBD_API_T;

extern const  USBD_API_T usb_api;

#ifdef __cplusplus
}
#endif 

#endif /*__MW_USBD_ROM_API_H*/

