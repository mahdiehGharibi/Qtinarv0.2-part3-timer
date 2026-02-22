#include "memory.h"

static unsigned char heap[1024 * 1024]; // 1 MB heap
static unsigned int heap_index = 0;

void* malloc(unsigned int size) {
    void* ptr = &heap[heap_index];
    heap_index += size;
    return ptr;
}
