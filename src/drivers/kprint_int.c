#include "screen.h"

void kprint_int(int num) {
    char buf[16];
    int i = 0;

    if (num == 0) {
        kprint("0");
        return;
    }

    if (num < 0) {
        kprint("-");
        num = -num;
    }

    while (num > 0) {
        buf[i++] = '0' + (num % 10);
        num /= 10;
    }

    while (i--) {
        char c[2] = { buf[i], 0 };
        kprint(c);
    }
}
