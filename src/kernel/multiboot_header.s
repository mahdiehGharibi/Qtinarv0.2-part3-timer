    .section .multiboot
    .align 4

    .long 0x1BADB002          # magic
    .long 0x00                # flags
    .long -(0x1BADB002 + 0x00)  # checksum
