#include "debug/debug.h"
#include <stdio.h>

int main(void) {
    init_debug();

    message(DEBUG_DEBUG, "TEST", "1");
    message(DEBUG_INFO, "TEST", "2");
    message(DEBUG_WARN, "TEST", "3");
    message(DEBUG_ERROR, "TEST", "");
    message(DEBUG_FATAL, "TEST", "5");

    printf("Test 7\n");

    return 0;
}
