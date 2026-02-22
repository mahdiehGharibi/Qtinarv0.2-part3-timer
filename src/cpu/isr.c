#include "isr.h"
#include "../drivers/screen.h"

void kprint_int(int num);   // forward declaration

isr_t interrupt_handlers[256];


void register_interrupt_handler(uint8_t n, isr_t handler) {
    interrupt_handlers[n] = handler;
}

void isr_handler(registers_t* regs) {
    if (interrupt_handlers[regs->int_no]) {
        interrupt_handlers[regs->int_no](regs);
    } else {
        kprint("Unhandled interrupt: ");
        kprint_int(regs->int_no);
        kprint("\n");
    }
}
