#include "keyboard.h"
#include "../cpu/isr.h"
#include "../cpu/ports.h"
#include "../kernel/input.h"
#include "../drivers/screen.h"

unsigned char scancode_to_ascii[128] = {
    0, 27, '1','2','3','4','5','6','7','8','9','0','-','=', '\b',
    '\t','q','w','e','r','t','y','u','i','o','p','[',']','\n', 0,
    'a','s','d','f','g','h','j','k','l',';','\'','`', 0,'\\',
    'z','x','c','v','b','n','m',',','.','/', 0, '*', 0,' ',
};

void keyboard_handler(registers_t* regs) {
    unsigned char sc = inb(0x60);

    if (sc & 0x80) return; // ignore key releases

    if (sc == 14) { // backspace
        input_backspace();
        return;
    }

    if (sc == 28) { // enter
        input_submit();
        return;
    }

    char c = scancode_to_ascii[sc];
    if (c)
        input_add(c);
}

void keyboard_init() {
    register_interrupt_handler(33, keyboard_handler);
}
