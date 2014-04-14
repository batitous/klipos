
#include <libs-klipos.h>

//uint8_t usb_RomDriver_buffer[USB_ROM_SIZE] __attribute__((section("USB_RAM")));


void initUsbHardware(void)
{
    SETBIT(LPC_IOCON->PIO0_3, 0);
    SETBIT(LPC_IOCON->PIO0_6, 0);

    // power on usb and usb ram
    SETBIT(LPC_SYSCON->SYSAHBCLKCTRL,14);
    SETBIT(LPC_SYSCON->SYSAHBCLKCTRL,27);

    // power up usb PHY and PLL
    CLRBIT(LPC_SYSCON->PDRUNCFG,10);
    CLRBIT(LPC_SYSCON->PDRUNCFG,8);

    LPC_SYSCON->USBPLLCLKSEL  = 1; // select system osc  
    LPC_SYSCON->USBPLLCTRL = 0x23; //(3 & 0x1F) | ((1 & 0x3) << 5);

    while (!(LPC_SYSCON->USBPLLSTAT & 0x01));     // Wait Until PLL Locked

    LPC_SYSCON->USBCLKSEL     = 0; // select usb pll out
    LPC_SYSCON->USBCLKDIV     = 1; 

}
