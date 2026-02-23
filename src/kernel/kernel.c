#include "../drivers/screen.h"
#include "../drivers/keyboard.h"
#include "../kernel/input.h"
#include "../cpu/timer.h"
#include "../cpu/gdt.h"
#include "../cpu/idt.h"
#include "../cpu/isr.h"
#include "../cpu/irq.h"

void kernel_main() {
    clear_screen();

    set_color(0xB, 0x0);
    kprint("QtinarOS v0.2\n");
    set_color(0x7, 0x0);
    kprint("Initializing system...\n");

    init_gdt();
    init_idt();
    isr_install();
    irq_install();

    kprint("CPU initialized.\n");

    input_init();
    init_timer(100);
    keyboard_init();

    kprint("Drivers initialized.\n\n");

    set_color(0xA, 0x0);
    kprint("> ");
    set_color(0x7, 0x0);

    asm volatile("sti");

    while (1) {
        asm volatile("hlt");
    }
}
