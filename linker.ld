ENTRY(_start)

SECTIONS
{
    . = 1M;

    .text : {
        *(.multiboot)   /* put header first in .text */
        *(.text*)
    }

    .rodata : {
        *(.rodata*)
    }

    .data : {
        *(.data*)
    }

    .bss : {
        *(COMMON)
        *(.bss*)
    }
}
