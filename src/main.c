#include "debug/debug.h"
#include "fibonacci/fibonacci.h"

int main(void) {
    init_debug();

    // run_fibonacci_examples();

    message(DEBUG_DEBUG, "TEST", "1");
    message(DEBUG_INFO, "TEST", "2");
    message(DEBUG_WARN, "TEST", "3");
    message(DEBUG_ERROR, "TEST", "");
    message(DEBUG_FATAL, "TEST", "5");

    return 0;
}
