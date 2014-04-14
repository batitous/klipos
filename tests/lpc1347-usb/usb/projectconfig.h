/* 
 * File:   projectconfig.h
 * Author: baptiste
 *
 * Created on 14 avril 2014, 10:15
 */

#ifndef PROJECTCONFIG_H
#define	PROJECTCONFIG_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <libs-klipos.h>
    
#define CFG_MCU_FAMILY_LPC13UXX
#define CFG_ENABLE_USB
    
#define CFG_PRINTF_USBCDC

#define CFG_USB_STRING_MANUFACTURER       "microBuilder.eu"
#define CFG_USB_STRING_PRODUCT            "LPC1347 LPCXpresso"
#define CFG_USB_VENDORID                  (0x1FC9)

#define CFG_USB_CDC
#define CFG_USB
    
#define ASSERT_MESSAGE(i,a,d)
#define ASSERT(a,e)
    
#ifdef	__cplusplus
}
#endif

#endif	/* PROJECTCONFIG_H */

