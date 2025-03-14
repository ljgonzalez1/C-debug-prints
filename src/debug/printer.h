#ifndef PRINTER_H
#define PRINTER_H

typedef enum {
    DEBUG_INFO,
    DEBUG_WARN,
    DEBUG_ERROR,
    DEBUG_DEBUG,
    DEBUG_FATAL
} DebugType;

// Variable global para habilitar/deshabilitar colores ANSI
extern int debug_colors_supported;

// Función principal de impresión
void print_debug(DebugType type, const char *msg, const char *detail);

#endif // PRINTER_H
