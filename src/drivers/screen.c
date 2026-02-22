#include "screen.h"
#include "../cpu/ports.h"

#define VIDEO_ADDRESS 0xB8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define WHITE_ON_BLACK 0x0F

int get_cursor_offset() {
    outb(0x3D4, 14);
    int high = inb(0x3D5);

    outb(0x3D4, 15);
    int low = inb(0x3D5);

    int offset = (high << 8) + low;
    return offset * 2;
}

void set_cursor_offset(int offset) {
    offset /= 2;

    outb(0x3D4, 14);
    outb(0x3D5, (unsigned char)(offset >> 8));

    outb(0x3D4, 15);
    outb(0x3D5, (unsigned char)(offset & 0xFF));
}

static int cursor_row = 0;
static int cursor_col = 0;
static unsigned char *video = (unsigned char *)VIDEO_ADDRESS;

void kprint_backspace() {
    int offset = get_cursor_offset() - 2; // move back one character
    if (offset < 0) offset = 0;

    set_cursor_offset(offset);
    char* vidmem = (char*) VIDEO_ADDRESS;
    vidmem[offset] = ' ';
    vidmem[offset + 1] = WHITE_ON_BLACK;

    set_cursor_offset(offset);
}


static void move_cursor() {
    unsigned short pos = cursor_row * MAX_COLS + cursor_col;
    outb(0x3D4, 0x0F);
    outb(0x3D5, (unsigned char)(pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (unsigned char)((pos >> 8) & 0xFF));
}

void clear_screen() {
    for (int row = 0; row < MAX_ROWS; row++) {
        for (int col = 0; col < MAX_COLS; col++) {
            int idx = 2 * (row * MAX_COLS + col);
            video[idx] = ' ';
            video[idx + 1] = WHITE_ON_BLACK;
        }
    }
    cursor_row = 0;
    cursor_col = 0;
    move_cursor();
}

void kprint_char(char c) {
    if (c == '\n') {
        cursor_row++;
        cursor_col = 0;
        move_cursor();
        return;
    }

    int idx = 2 * (cursor_row * MAX_COLS + cursor_col);
    video[idx] = c;
    video[idx + 1] = WHITE_ON_BLACK;

    cursor_col++;
    if (cursor_col >= MAX_COLS) {
        cursor_col = 0;
        cursor_row++;
    }

    if (cursor_row >= MAX_ROWS) {
        cursor_row = 0;
    }

    move_cursor();
}

void kprint(const char *str) {
    while (*str) {
        kprint_char(*str++);
    }
}
