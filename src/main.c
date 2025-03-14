#include "debug/debug.h"
#include "fibonacci/fibonacci.h"

int main(void) {
    init_debug();

    // Ejemplo simple de uso
    //message(DEBUG_INFO, "Comenzando Fibonacci Demo Creativa", "");

    // run_fibonacci_examples();

    // message(DEBUG_WARN, "Programa finalizado, revisa mensajes anteriores para ver la salida completa.", "");

    message(DEBUG_DEBUG, "TEST", "1");
    message(DEBUG_INFO, "TEST", "2");
    message(DEBUG_WARN, "TEST", "3");
    message(DEBUG_ERROR, "TEST", "");
    message(DEBUG_FATAL, "TEST", "5");

    return 0;
}
