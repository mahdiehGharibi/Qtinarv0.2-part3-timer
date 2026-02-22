#ifndef SCREEN_H
#define SCREEN_H

int get_cursor_offset();
void clear_screen();
void kprint(const char* str);
void kprint_char(char c);
void kprint_int(int num);
void set_cursor_offset(int offset);

#endif
