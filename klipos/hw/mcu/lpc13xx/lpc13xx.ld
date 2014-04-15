/*
 * generic gcc linker script for LPC13XX
 * Taken from Kamal Mostafa <kamal@whence.com>.
 *
 * License: Public Domain
 */

MEMORY
{
    FLASH (rx)    : ORIGIN = 0x00000000, LENGTH = 32K 
    RAM (rwx)     : ORIGIN = 0x10000000, LENGTH = 8192 - 32
    USBRAM (rwx)  : ORIGIN = 0x20004000, LENGTH = 0x800   /* 2k  */
}

SECTIONS
{
    .text :
    {
        _text = .;
        KEEP(*(.isr_vector))
        KEEP(*(.after_vectors))
        *(.text*)
        *(.rodata*)
        _etext = .;
    } > FLASH

    .data : AT (ADDR(.text) + SIZEOF(.text))
    {
        KEEP(*(.stack))
        _data = .;
        *(vtable)
        *(.data*)
        _edata = .;
    } > RAM

    .bss :
    {
        _bss = .;
        *(.bss*)
        *(COMMON)
        _ebss = .;
    } > RAM

}
