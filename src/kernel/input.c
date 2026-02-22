#include "input.h"
#include "../drivers/screen.h"
#include "commands.h"
#include <stddef.h>

static char* buffer = 0;
static size_t length = 0;
static size_t capacity = 0;

static void ensure_capacity(size_t new_len) {
    if (new_len <= capacity) return;

    size_t new_cap = capacity == 0 ? 64 : capacity * 2;
    while (new_cap < new_len) new_cap *= 2;

    char* new_buf = (char*)malloc(new_cap);
    for (size_t i = 0; i < length; i++)
        new_buf[i] = buffer[i];

    buffer = new_buf;
    capacity = new_cap;
}

void input_add(char c) {
    ensure_capacity(length + 2);
    buffer[length++] = c;
    buffer[length] = 0;

    char s[2] = {c, 0};
    kprint(s);
}

void input_backspace() {
    if (length == 0) return;

    length--;
    buffer[length] = 0;

    kprint_backspace();
}


void input_submit() {
    if (length == 0) {
        kprint("\n> ");
        return;
    }

    buffer[length] = 0;
    kprint("\n");

    run_command(buffer);

    length = 0;
    kprint("> ");
}
