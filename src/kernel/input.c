#include "input.h"
#include "commands.h"          
#include "../drivers/screen.h"
#include "../libc/string.h"

static char input_buffer[256];
static int input_length = 0;

void input_init() {
    input_length = 0;
    input_buffer[0] = '\0';
}

void input_backspace() {
    if (input_length > 0) {
        input_length--;
        input_buffer[input_length] = '\0';
        kprint_backspace();
    }
}

void input_append(char c) {
    if (input_length < 255) {
        input_buffer[input_length++] = c;
        input_buffer[input_length] = '\0';
        char s[2] = { c, '\0' };
        kprint(s);
    }
}

void input_submit() {
    kprint("\n");

    handle_command(input_buffer);   

    input_length = 0;
    input_buffer[0] = '\0';

    set_color(0xA, 0x0); 
    kprint("> ");
    set_color(0x7, 0x0);
}
