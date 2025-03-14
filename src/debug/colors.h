#pragma once

#ifdef _WIN32
#include <windows.h>
#include <io.h>

// Simple detección: Intento de ver si la consola Win10 o superior soporta
// secuencias ANSI. Para la mayoría de shells, puede requerir habilitar VT100.
// Por simplicidad, retornamos 1 si se puede setear modo. O dev 0 si no.
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
    // Asumimos 1 en Linux/macOS. Se puede refinar con isatty, etc.
    return 1;
}
#endif

// ANSI escapes
#define ANSI_RESET       "\033[0m"
#define ANSI_BOLD        "\033[1m"
#define ANSI_ITALIC      "\033[3m"
#define ANSI_UNDERLINE   "\033[4m"

// Colores
#define ANSI_FG_RED      "\033[31m"
#define ANSI_FG_GREEN    "\033[32m"
#define ANSI_FG_YELLOW   "\033[33m"
#define ANSI_FG_BLUE     "\033[34m"
#define ANSI_FG_MAGENTA  "\033[35m"
#define ANSI_FG_CYAN     "\033[36m"
#define ANSI_FG_WHITE    "\033[37m"
