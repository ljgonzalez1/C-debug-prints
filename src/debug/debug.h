#ifndef DEBUG_H
#define DEBUG_H

#include "printer.h"

void init_debug(void);

void message(DebugType type, const char *msg_fmt, const char *detail_fmt, ...);

#endif // DEBUG_H
