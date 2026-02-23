#include "keyboard.h"
#include "../cpu/isr.h"
#include "../cpu/ports.h"
#include "../kernel/input.h"
#include "../cpu/irq.h"

unsigned char scancode_to_ascii[128] = {
    0, 27, '1','2','3','4','5','6','7','8','9','0','-','=', '\b',
    '\t','q','w','e','r','t','y','u','i','o','p','[',']','\n', 0,
    'a','s','d','f','g','h','j','k','l',';','\'','`', 0,'\\',
    'z','x','c','v','b','n','m',',','.','/', 0, '*', 0,' ',
};

void keyboard_handler(registers_t* regs) {
    (void)regs;

    unsigned char sc = inb(0x60);

    if (sc & 0x80) return;

    if (sc == 14) {
        input_backspace();
        return;
    }

    if (sc == 28) {
        input_submit();
        return;
    }

    char c = scancode_to_ascii[sc];
    if (c) input_append(c);
}

void keyboard_init() {
    register_interrupt_handler(IRQ1, keyboard_handler);

    uint8_t mask = inb(0x21);
    mask &= ~(1 << 1);   // enable IRQ1
    outb(0x21, mask);
}
