#include "debug.h"
#include "printer.h"
#include "timer.h"
#include "colors.h"
#include <stdarg.h>
#include <string.h>
#include <stdio.h>

int debug_colors_supported = 0;

void init_debug(void) {
    init_time();
    debug_colors_supported = supports_color();
}

void message(DebugType type, const char *msg_fmt, const char *detail_fmt, ...) {
    char msg[1024];
    char detail[1024] = "";

    va_list args;
    va_start(args, detail_fmt);

    vsnprintf(msg, sizeof(msg), msg_fmt, args);

    if (detail_fmt && strlen(detail_fmt) > 0) {
        vsnprintf(detail, sizeof(detail), detail_fmt, args);
    }

    va_end(args);

    if (strlen(detail) == 0)
        print_debug(type, msg, NULL);
    else
        print_debug(type, msg, detail);
}
