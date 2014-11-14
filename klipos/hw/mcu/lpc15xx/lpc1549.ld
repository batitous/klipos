/*
 * generic gcc linker script for LPC1549
 * Taken from Kamal Mostafa <kamal@whence.com>.
 *
 * License: Public Domain
 */

MEMORY
{
    FLASH (rx)    : ORIGIN = 0x00000000, LENGTH = 256K 
    RAM (rwx)     : ORIGIN = 0x02000000, LENGTH = 16K
    RAM1 (rwx)    : ORIGIN = 0x02004000, LENGTH = 16K
    RAM2 (rwx)    : ORIGIN = 0x02008000, LENGTH = 4K
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

    .data : 
    {
        __stack_start__ = .; /* start of the stack section */
        KEEP(*(.stack))
         . = ALIGN(4);
        __stack_end__ = .;   /* end of the stack section */

        _data = .;
        *(vtable)
        *(.data*)
        _edata = .;
    } > RAM AT > FLASH

    .bss :
    {
        _bss = .;
        *(.bss*)
        *(COMMON)
        _ebss = .;
    } > RAM

}
