#include "screen.h"
#include "../cpu/ports.h"

#define VIDEO_ADDRESS 0xB8000
#define MAX_ROWS 25
#define MAX_COLS 80

/* Color definitions */
#define BLACK         0x0
#define BLUE          0x1
#define GREEN         0x2
#define CYAN          0x3
#define RED           0x4
#define MAGENTA       0x5
#define BROWN         0x6
#define LIGHT_GREY    0x7
#define DARK_GREY     0x8
#define LIGHT_BLUE    0x9
#define LIGHT_GREEN   0xA
#define LIGHT_CYAN    0xB
#define LIGHT_RED     0xC
#define LIGHT_MAGENTA 0xD
#define YELLOW        0xE
#define WHITE         0xF

#define WHITE_ON_BLACK ((BLACK << 4) | WHITE)

static int cursor_row = 0;
static int cursor_col = 0;
static unsigned char *video = (unsigned char *)VIDEO_ADDRESS;
static unsigned char current_color = WHITE_ON_BLACK;

void set_color(unsigned char fg, unsigned char bg) {
    current_color = (bg << 4) | (fg & 0x0F);
}

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

void kprint_backspace() {
    int offset = get_cursor_offset() - 2;
    if (offset < 0) offset = 0;

    char* vidmem = (char*) VIDEO_ADDRESS;
    vidmem[offset] = ' ';
    vidmem[offset + 1] = current_color;

    int pos = offset / 2;
    cursor_row = pos / MAX_COLS;
    cursor_col = pos % MAX_COLS;

    set_cursor_offset(offset);
}

static void move_cursor() {
    unsigned short pos = cursor_row * MAX_COLS + cursor_col;
    outb(0x3D4, 0x0F);
    outb(0x3D5, (unsigned char)(pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (unsigned char)((pos >> 8) & 0xFF));
}

static void scroll() {
    if (cursor_row < MAX_ROWS)
        return;

    for (int row = 1; row < MAX_ROWS; row++) {
        for (int col = 0; col < MAX_COLS; col++) {
            int from = 2 * (row * MAX_COLS + col);
            int to   = 2 * ((row - 1) * MAX_COLS + col);
            video[to]     = video[from];
            video[to + 1] = video[from + 1];
        }
    }

    for (int col = 0; col < MAX_COLS; col++) {
        int idx = 2 * ((MAX_ROWS - 1) * MAX_COLS + col);
        video[idx]     = ' ';
        video[idx + 1] = current_color;
    }

    cursor_row = MAX_ROWS - 1;
    cursor_col = 0;
    move_cursor();
}

void clear_screen() {
    for (int row = 0; row < MAX_ROWS; row++) {
        for (int col = 0; col < MAX_COLS; col++) {
            int idx = 2 * (row * MAX_COLS + col);
            video[idx]     = ' ';
            video[idx + 1] = current_color;
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
        scroll();
        move_cursor();
        return;
    }

    int idx = 2 * (cursor_row * MAX_COLS + cursor_col);
    video[idx]     = c;
    video[idx + 1] = current_color;

    cursor_col++;
    if (cursor_col >= MAX_COLS) {
        cursor_col = 0;
        cursor_row++;
    }

    scroll();
    move_cursor();
}

void kprint(const char *str) {
    while (*str) {
        kprint_char(*str++);
    }
}
