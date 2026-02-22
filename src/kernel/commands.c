#include "commands.h"
#include "../drivers/screen.h"
#include "../libc/string.h"

void run_command(const char* cmd) {
    if (strcmp(cmd, "help") == 0) {
        kprint("Commands:\n");
        kprint("  help  - show this message\n");
        kprint("  clear - clear the screen\n");
        kprint("  echo <text>\n");
        return;
    }

    if (strcmp(cmd, "clear") == 0) {
        clear_screen();
        return;
    }

    if (strncmp(cmd, "echo ", 5) == 0) {
        kprint(cmd + 5);
        kprint("\n");
        return;
    }

    kprint("Unknown command: ");
    kprint(cmd);
    kprint("\n");
}
