#include "commands.h"
#include "../drivers/screen.h"
#include "../libc/string.h"
#include "../cpu/time.h"

/* Forward declaration because we don't include kprint_int.h */
void kprint_int(int value);

void handle_command(char *input) {

    if (strcmp(input, "help") == 0) {
        set_color(0xB, 0x0); // LIGHT_CYAN
        kprint("Commands:\n");
        kprint("  help    - show this message\n");
        kprint("  clear   - clear the screen\n");
        kprint("  echo X  - print X\n");
        kprint("  uptime  - show timer ticks and seconds\n");
        set_color(0x7, 0x0);
        return;
    }

    if (strcmp(input, "uptime") == 0) {
        set_color(0xA, 0x0); // LIGHT_GREEN
        kprint("Ticks: ");
        kprint_int(timer_ticks());
        kprint("\nSeconds: ");
        kprint_int(timer_seconds());
        kprint("\n");
        set_color(0x7, 0x0);
        return;
    }

    if (strcmp(input, "clear") == 0) {
        clear_screen();
        set_color(0xA, 0x0);
        kprint("> ");
        set_color(0x7, 0x0);
        return;
    }

    if (strncmp(input, "echo ", 5) == 0) {
        set_color(0x7, 0x0);
        kprint(input + 5);
        kprint("\n");
        return;
    }

    set_color(0xC, 0x0); // LIGHT_RED
    kprint("Unknown command: ");
    kprint(input);
    kprint("\n");
    set_color(0x7, 0x0);
}
