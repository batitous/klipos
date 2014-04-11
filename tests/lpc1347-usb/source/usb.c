
#include <libs-klipos.h>

#include "../include/romapi_13xx.h"

#include "../include/usbd_rom/inc/usbd_rom_api.h"


#define LPC_ROM_API_BASE_LOC      0x1FFF1FF8
#define LPC_USB0_BASE             LPC_USB_BASE

#define LPC_ROM_API               (*((LPC_ROM_API_T        * *) LPC_ROM_API_BASE_LOC))


static USBD_HANDLE_T g_hUsb;

const  USBD_API_T *g_pUsbApi;

extern ErrorCode_t vcom_init(USBD_HANDLE_T hUsb, USB_CORE_DESCS_T *pDesc, USBD_API_INIT_PARAM_T *pUsbParam);


void USB_IRQn_Handler(void)
{
    uint32_t *addr = (uint32_t *) LPC_USB->EPLISTSTART;

    /*	WORKAROUND for artf32289 ROM driver BUG:
        As part of USB specification the device should respond
        with STALL condition for any unsupported setup packet. The host will send
        new setup packet/request on seeing STALL condition for EP0 instead of sending
        a clear STALL request. Current driver in ROM doesn't clear the STALL
        condition on new setup packet which should be fixed.
     */
    if ( LPC_USB->DEVCMDSTAT & BIT(8) ) 
    {
        /* if setup packet is received */
        addr[0] &= ~(BIT(29));	/* clear EP0_OUT stall */
        addr[2] &= ~(BIT(29));	/* clear EP0_IN stall */
    }

    g_pUsbApi->hw->ISR(g_hUsb);
}

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

void initUsbCdcStack(void)
{
    USBD_API_INIT_PARAM_T usb_param;
    USB_CORE_DESCS_T desc;
    ErrorCode_t ret = LPC_OK;
    
    /* initialize USBD ROM API pointer. */
    g_pUsbApi = (const USBD_API_T *) LPC_ROM_API->usbdApiBase;

    /* initialize call back structures */
    memset((void *) &usb_param, 0, sizeof(USBD_API_INIT_PARAM_T));
    usb_param.usb_reg_base = LPC_USB0_BASE;

    /*	WORKAROUND for artf44835 ROM driver BUG:
        Code clearing STALL bits in endpoint reset routine corrupts memory area
        next to the endpoint control data. For example When EP0, EP1_IN, EP1_OUT,
        EP2_IN are used we need to specify 3 here. But as a workaround for this
        issue specify 4. So that extra EPs control structure acts as padding buffer
        to avoid data corruption. Corruption of padding memory doesn’t affect the
        stack/program behaviour.
     */
    usb_param.max_num_ep = 3 + 1;
    usb_param.mem_base = USB_STACK_MEM_BASE;
    usb_param.mem_size = USB_STACK_MEM_SIZE;

    /* Set the USB descriptors */
    desc.device_desc = (uint8_t *) &USB_DeviceDescriptor[0];
    desc.string_desc = (uint8_t *) &USB_StringDescriptor[0];

    /* Note, to pass USBCV test full-speed only devices should have both
       descriptor arrays point to same location and device_qualifier set to 0.
     */
    desc.high_speed_desc = (uint8_t *) &USB_FsConfigDescriptor[0];
    desc.full_speed_desc = (uint8_t *) &USB_FsConfigDescriptor[0];
    desc.device_qualifier = 0;

    /* USB Initialization */
    ret = g_pUsbApi->hw->Init(&g_hUsb, &desc, &usb_param);
    if (ret == LPC_OK)
    {
        /*	WORKAROUND for artf32219 ROM driver BUG:
            The mem_base parameter part of USB_param structure returned
            by Init() routine is not accurate causing memory allocation issues for
            further components.
         */
        usb_param.mem_base = USB_STACK_MEM_BASE + (USB_STACK_MEM_SIZE - usb_param.mem_size);

        /* Init VCOM interface */
        ret = vcom_init(g_hUsb, &desc, &usb_param);
        
        if (ret == LPC_OK) 
        {
            /*  enable USB interrupts */
            NVIC_EnableIRQ(USB_IRQn);
            /* now connect */
            g_pUsbApi->hw->Connect(g_hUsb, 1);
        }
    }
}

/* Find the address of interface descriptor for given class type. */
USB_INTERFACE_DESCRIPTOR *find_IntfDesc(const uint8_t *pDesc, uint32_t intfClass)
{
    USB_COMMON_DESCRIPTOR *pD;
    USB_INTERFACE_DESCRIPTOR *pIntfDesc = 0;
    uint32_t next_desc_adr;

    pD = (USB_COMMON_DESCRIPTOR *) pDesc;
    next_desc_adr = (uint32_t) pDesc;

    while (pD->bLength) 
    {
        /* is it interface descriptor */
        if (pD->bDescriptorType == USB_INTERFACE_DESCRIPTOR_TYPE) 
        {
            pIntfDesc = (USB_INTERFACE_DESCRIPTOR *) pD;
            /* did we find the right interface descriptor */
            if (pIntfDesc->bInterfaceClass == intfClass) 
            {
                break;
            }
        }
        pIntfDesc = 0;
        next_desc_adr = (uint32_t) pD + pD->bLength;
        pD = (USB_COMMON_DESCRIPTOR *) next_desc_adr;
    }

    return pIntfDesc;
}

