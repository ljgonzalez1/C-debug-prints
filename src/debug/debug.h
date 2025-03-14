#ifndef DEBUG_H
#define DEBUG_H

#include "printer.h"

// Inicializa el sistema de debug (timer + soporte colores)
void init_debug(void);

// Función genérica con formato variádico
void message(DebugType type, const char *msg_fmt, const char *detail_fmt, ...);

#endif // DEBUG_H
