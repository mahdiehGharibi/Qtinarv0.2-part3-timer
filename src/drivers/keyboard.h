#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "../cpu/isr.h"

void keyboard_init(void);
void keyboard_handler(registers_t* regs);

#endif
