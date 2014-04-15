
#include <libs-klipos.h>

//uint8_t usb_RomDriver_buffer[USB_ROM_SIZE] __attribute__((section("USB_RAM")));

/*
void initLowLevelCpu(void)
{
    uint32_t i;
    
    LPC_SYSCON->PDRUNCFG     &= ~(1 << 5);          // Power-up System Osc      
    LPC_SYSCON->SYSOSCCTRL    = 0x0;
  
    for (i = 0; i < 200; i++) __NOP();
    
    LPC_SYSCON->SYSPLLCLKSEL  = 0x1;
   
    LPC_SYSCON->SYSPLLCTRL    = 0x25;
    LPC_SYSCON->PDRUNCFG     &= ~(1 << 7);          // Power-up SYSPLL          
    while (!(LPC_SYSCON->SYSPLLSTAT & 0x01));	      // Wait Until PLL Locked  

    LPC_SYSCON->MAINCLKSEL    = 0x3;     // Select PLL Clock Output  
    LPC_SYSCON->SYSAHBCLKDIV  = 0x1;

    
    // USB part
    LPC_SYSCON->PDRUNCFG     &= ~(1 << 10);         // Power-up USB PHY         

    // Regardless USB PLL is used as USB clock or not, USB PLL needs to be configured.
    LPC_SYSCON->PDRUNCFG     &= ~(1 <<  8);         // Power-up USB PLL         
    LPC_SYSCON->USBPLLCLKSEL  = 0x1;   // Select PLL Input         
    LPC_SYSCON->USBPLLCTRL    = 0x23;
    while (!(LPC_SYSCON->USBPLLSTAT   & 0x01));     // Wait Until PLL Locked    

    LPC_SYSCON->USBCLKSEL     = 0x0;      // Select USB Clock         
    LPC_SYSCON->USBCLKDIV     = 0x1;      // Set USB clock divider      
}
*/

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
