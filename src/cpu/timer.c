#include "timer.h"
#include "isr.h"
#include "irq.h"
#include "ports.h"
#include "../drivers/screen.h"

unsigned int tick = 0;

static void timer_callback(registers_t *regs) {
    tick++;
}

void init_timer(int frequency) {
    register_interrupt_handler(IRQ0, timer_callback);

    int divisor = 1193182 / frequency;

    outb(0x43, 0x36);

    unsigned char low  = (unsigned char)(divisor & 0xFF);
    unsigned char high = (unsigned char)((divisor >> 8) & 0xFF);

    outb(0x40, low);
    outb(0x40, high);
}
