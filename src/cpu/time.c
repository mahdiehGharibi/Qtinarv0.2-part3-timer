#include "time.h"
#include "timer.h"

extern unsigned int tick;

unsigned int timer_ticks() {
    return tick;
}

unsigned int timer_seconds() {
    return tick / 100; // 100 Hz
}

void sleep(unsigned int ms) {
    unsigned int ticks_to_wait = ms / 10; // 100 Hz = 10ms per tick
    unsigned int target = tick + ticks_to_wait;

    while (tick < target) {
        asm volatile("hlt");
    }
}
