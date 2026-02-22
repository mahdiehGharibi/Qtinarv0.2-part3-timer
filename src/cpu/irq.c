#include "irq.h"
#include "ports.h"
#include "isr.h"

extern isr_t interrupt_handlers[256];


void irq_handler(registers_t* regs) {
    if (interrupt_handlers[regs->int_no])
        interrupt_handlers[regs->int_no](regs);

    if (regs->int_no >= 40)
        outb(0xA0, 0x20);

    outb(0x20, 0x20);
}
