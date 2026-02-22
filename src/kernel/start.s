.intel_syntax noprefix

.section .multiboot
.align 4
.globl multiboot_header

multiboot_header:
    .long 0x1BADB002
    .long 0x00
    .long -(0x1BADB002 + 0x00)

.section .text
.globl _start
.extern kernel_main

_start:
    cli
    mov esp, 0x90000
    call kernel_main
hang:
    hlt
    jmp hang
