#include "../drivers/screen.h"
#include "../cpu/gdt.h"
#include "../cpu/idt.h"
#include "../cpu/pic.h"
#include "../drivers/keyboard.h"

void kernel_main() {
    clear_screen();

    gdt_init();
    idt_init();
    pic_init();
    keyboard_init();

    kprint("QtinarOS ready.\n");
    kprint("> ");

    asm volatile("sti");

    while (1) {}
}
