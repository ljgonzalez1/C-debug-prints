#ifndef PRINTER_H
#define PRINTER_H

typedef enum {
    DEBUG_INFO,
    DEBUG_WARN,
    DEBUG_ERROR,
    DEBUG_DEBUG,
    DEBUG_FATAL
} DebugType;

extern int debug_colors_supported;

void print_debug(DebugType type, const char *msg, const char *detail);

#endif
