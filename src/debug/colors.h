#pragma once

#ifdef _WIN32
#include <windows.h>
#include <io.h>

static inline int supports_color() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) return 0;
    DWORD mode = 0;
    if (!GetConsoleMode(hOut, &mode)) return 0;
    // Intentamos habilitar ENABLE_VIRTUAL_TERMINAL_PROCESSING
    mode |= 0x0004; // ENABLE_VIRTUAL_TERMINAL_PROCESSING
    if (!SetConsoleMode(hOut, mode)) return 0;
    return 1;
}
#else
#include <unistd.h>
static inline int supports_color() {
    return 1;
}
#endif

// ANSI escapes
#define ANSI_RESET       "\033[0m"
#define ANSI_BOLD        "\033[1m"
#define ANSI_ITALIC      "\033[3m"
#define ANSI_UNDERLINE   "\033[4m"

// Colors
#define ANSI_FG_RED      "\033[31m"
#define ANSI_FG_GREEN    "\033[32m"
#define ANSI_FG_YELLOW   "\033[33m"
#define ANSI_FG_BLUE     "\033[34m"
#define ANSI_FG_MAGENTA  "\033[35m"
#define ANSI_FG_CYAN     "\033[36m"
#define ANSI_FG_WHITE    "\033[37m"
