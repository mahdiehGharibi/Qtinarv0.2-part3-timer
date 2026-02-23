#include "irq.h"
#include "ports.h"
#include "idt.h"
#include "isr.h"
#include "pic.h"
#include "../drivers/screen.h"

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

extern isr_t interrupt_handlers[256];

void irq_install(void) {
    pic_remap(0x20, 0x28);

    idt_set_gate(IRQ0, (uint32_t)irq0,  0x08, 0x8E);
    idt_set_gate(IRQ1, (uint32_t)irq1,  0x08, 0x8E);
    idt_set_gate(IRQ2, (uint32_t)irq2,  0x08, 0x8E);
    idt_set_gate(IRQ3, (uint32_t)irq3,  0x08, 0x8E);
    idt_set_gate(IRQ4, (uint32_t)irq4,  0x08, 0x8E);
    idt_set_gate(IRQ5, (uint32_t)irq5,  0x08, 0x8E);
    idt_set_gate(IRQ6, (uint32_t)irq6,  0x08, 0x8E);
    idt_set_gate(IRQ7, (uint32_t)irq7,  0x08, 0x8E);
    idt_set_gate(IRQ8, (uint32_t)irq8,  0x08, 0x8E);
    idt_set_gate(IRQ9, (uint32_t)irq9,  0x08, 0x8E);
    idt_set_gate(IRQ10, (uint32_t)irq10, 0x08, 0x8E);
    idt_set_gate(IRQ11, (uint32_t)irq11, 0x08, 0x8E);
    idt_set_gate(IRQ12, (uint32_t)irq12, 0x08, 0x8E);
    idt_set_gate(IRQ13, (uint32_t)irq13, 0x08, 0x8E);
    idt_set_gate(IRQ14, (uint32_t)irq14, 0x08, 0x8E);
    idt_set_gate(IRQ15, (uint32_t)irq15, 0x08, 0x8E);
}

void irq_handler(registers_t* regs) {
    if (interrupt_handlers[regs->int_no]) {
        interrupt_handlers[regs->int_no](regs);
    }

    if (regs->int_no >= 40)
        outb(0xA0, 0x20);

    outb(0x20, 0x20);
}

