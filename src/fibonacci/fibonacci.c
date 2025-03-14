#include "fibonacci.h"
#include "../debug/debug.h"   // Para message(), DebugType, etc.
#include "../debug/timer.h"   // Para get_elapsed_time()
#include <unistd.h>           // Para sleep() en Linux/macOS (en Windows, usar Sleep(ms))

// Ejecuta la secuencia de fibonacci con debug
void run_fibonacci(int n) {
    if (n <= 0) {
        message(DEBUG_ERROR, "El valor no puede ser negativo ni cero.", "");
        return;
    }

    long long a = 0, b = 1, temp;

    message(DEBUG_DEBUG, "Iniciando secuencia Fibonacci", "Variables inicializadas correctamente");

    // Imprime primer término
    message(DEBUG_INFO, "[ %11.6f ] INFO : Nro. %lld", "", get_elapsed_time(), a);

    for (int i = 1; i < n; i++) {
        message(DEBUG_INFO, "[ %11.6f ] INFO : Nro. %lld", "", get_elapsed_time(), b);
        temp = a + b;
        a = b;
        b = temp;
    }
}

// Muestra ejemplos creativos de mensaje
void run_fibonacci_examples(void) {
    // Ejemplo con multilinea en message() sin detail
    message(DEBUG_WARN, "Esto es un mensaje muy largo en el que quise meter un \\n. "
           "Si no meto eso, no \\n debería hacer salto alineado con espacios accidentales, "
           "que serán\\n impresos de todas formas",
           "");

    message(DEBUG_INFO, "Este mensaje tiene un color rojo real \033[31m(Rojo activo)\033[0m "
           "y este es literal '\\033[32m' no cambia color",
           "");

    message(DEBUG_DEBUG,
            "un caso extraño en el que \nel usuario usa saltos de línea\n"
            "no requiere alineación, pues no usó el símbolo\n\\n en su string,\n"
            "pero si lo usa, hay que realinear",
            "espero hayas entendido\nesta parte...");

    message(DEBUG_ERROR, "Mensaje ERR con alineación especial, necesita dos espacios "
           "adicionales después del tipo.",
           "");

    run_short_sequence();

    message(DEBUG_INFO, "Secuencia larga después de una pausa para mostrar timer largo...", "");
    sleep(2);  // Espera 2s (ajusta a 1000 en Linux si deseas 1000s)
    message(DEBUG_INFO, "[ %11.6f ] INFO : Pasó demasiado tiempo así que cambio mi alineación "
           "para ajustar a ese número gigante que se escapa\nde la alineación anterior", "",
           get_elapsed_time());

    message(DEBUG_FATAL, "Simulación crítica de fin inesperado del programa.\n¡Fin!", "");
}

// Secuencia corta
void run_short_sequence(void) {
    run_fibonacci(5);
}
