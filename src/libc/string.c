#include "string.h"

int strcmp(const char* s1, const char* s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(unsigned char*)s1 - *(unsigned char*)s2;
}

int strncmp(const char* s1, const char* s2, size_t n) {
    while (n-- && *s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return n == (size_t)-1 ? 0 : *(unsigned char*)s1 - *(unsigned char*)s2;
}

size_t strlen(const char* s) {
    size_t len = 0;
    while (*s++) len++;
    return len;
}

void* memset(void* dest, int value, size_t count) {
    unsigned char* ptr = dest;
    while (count--) {
        *ptr++ = (unsigned char)value;
    }
    return dest;
}
