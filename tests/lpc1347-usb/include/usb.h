/* 
 * File:   usb.h
 * Author: baptiste
 *
 * Created on 11 avril 2014, 15:14
 */

#ifndef USB_H
#define	USB_H

#ifdef	__cplusplus
extern "C" {
#endif


extern void initUsbHardware(void);

extern void initUsbCdcStack(void);

#ifdef	__cplusplus
}
#endif

#endif	/* USB_H */

