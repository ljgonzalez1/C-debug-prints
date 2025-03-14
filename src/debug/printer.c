#ifdef _WIN32
// Para usar _strdup, deactivate warnings
#define _CRT_SECURE_NO_WARNINGS
#endif

#define _POSIX_C_SOURCE 200809L

#include "printer.h"
#include "colors.h"
#include "timer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// -------------------------------------------------------------------------
// Portable replacebent for my_srrdup (Windows vs Linux/macOS).
// -------------------------------------------------------------------------
static char* my_strdup(const char* s) {
    if (!s) return NULL;
#ifdef _WIN32
    return _strdup(s);
#else
    size_t len = strlen(s) + 1;
    char* res = (char*)malloc(len);
    if (res) {
        memcpy(res, s, len);
    }
    return res;
#endif
}

// -------------------------------------------------------------------------
// Formatting
// -------------------------------------------------------------------------
static void format_time(double t, char *dst, size_t size) {
    char temp[32];
    snprintf(temp, sizeof(temp), "%.6f", t); // p.ej. "1.234567", "12.345678"

    size_t len = strlen(temp);
    if (len == 0) {
        snprintf(dst, size, " 0.000000");
    } else if (len == 8) {
        // => "1.234567" => 2 espacios
        snprintf(dst, size, "  %s", temp);
    } else if (len == 9) {
        // => "12.345678" => 1 espacio
        snprintf(dst, size, " %s", temp);
    } else {
        // >=10 => sin espacios
        snprintf(dst, size, "%s", temp);
    }
}

// -------------------------------------------------------------------------
// Determina la cadena con el tipo y espacios adecuados
// -------------------------------------------------------------------------
static const char* get_type_suffix(DebugType type) {
    switch (type) {
        case DEBUG_INFO:  return "INFO :";
        case DEBUG_WARN:  return "WARN :";
        case DEBUG_ERROR: return "ERR  :";
        case DEBUG_DEBUG: return "DEBUG:";
        case DEBUG_FATAL: return "FATAL:";
        default:          return "???? :";
    }
}

// -------------------------------------------------------------------------
// Imprime un texto 'msg' en la PRIMERA línea con prefijo "prefix_ansi",
// alineando líneas siguientes (si msg tiene \n).
// -------------------------------------------------------------------------
static void print_multiline_msg(const char* msg,
                                const char* prefix_ansi,
                                int prefix_len,
                                const char* color)
{
    if (!msg || !*msg) return;

    char* copy = my_strdup(msg);
    if (!copy) return;

    char* saveptr = NULL;
    char* line = strtok_r(copy, "\n", &saveptr);

    int line_idx = 0;
    while (line) {
        if (line_idx == 0) {
            // Primera línea => prefix + line
            if (debug_colors_supported) {
                // color ya está re-aplicado en prefix_ansi, pero reafirmamos
                printf("%s%s\n", prefix_ansi, line);
                // no se hace un reset total, porque prefix_ansi ya incluyó el color
            } else {
                // sin color
                printf("%s%s\n", prefix_ansi, line);
            }
        } else {
            // Subsiguientes => prefix_len espacios + color + line
            char* spaces = malloc(prefix_len + 1);
            if (spaces) {
                memset(spaces, ' ', prefix_len);
                spaces[prefix_len] = '\0';
                if (debug_colors_supported && *color) {
                    printf("%s%s%s\n", spaces, color, line);
                    printf("%s", ANSI_RESET);
                } else {
                    printf("%s%s\n", spaces, line);
                }
                free(spaces);
            }
        }
        line = strtok_r(NULL, "\n", &saveptr);
        line_idx++;
    }

    free(copy);
}

// -------------------------------------------------------------------------
// Imprime 'detail' alineado EXACTAMENTE bajo el msg, con cursiva
// en la primera línea también (sin repetir prefix).
// => line_idx=0 => ya es una "línea subsecuente" => 'prefix_len' espacios
// -------------------------------------------------------------------------
static void print_detail(const char* detail,
                         int prefix_len,
                         const char* color)
{
    if (!detail || !*detail) return;

    char* copy = my_strdup(detail);
    if (!copy) return;

    char* saveptr = NULL;
    char* line = strtok_r(copy, "\n", &saveptr);

    int line_idx = 0;
    while (line) {
        // Cada línea => prefix_len espacios + color + italics + line
        char* spaces = malloc(prefix_len + 1);
        if (spaces) {
            memset(spaces, ' ', prefix_len);
            spaces[prefix_len] = '\0';

            if (debug_colors_supported && *color) {
                // italic + color
                printf("%s%s%s%s\n", spaces, color, ANSI_ITALIC, line);
                printf("%s", ANSI_RESET);
            } else {
                // sin color
                printf("%s%s\n", spaces, line);
            }
            free(spaces);
        }
        line = strtok_r(NULL, "\n", &saveptr);
        line_idx++;
    }
    free(copy);
}

// -------------------------------------------------------------------------
// Función principal: print_debug
// => Muestra [  0.123456 ] TIPO: Mensaje
//    y el detail alineado en cursiva
// -------------------------------------------------------------------------
void print_debug(DebugType type, const char *msg, const char *detail) {
    double t = get_elapsed_time();

    // 1) Arma el tiempo => "  1.234567", etc.
    char timebuf[32];
    format_time(t, timebuf, sizeof(timebuf));
    // => "[  1.234567 ]"
    char bracketed[64];
    snprintf(bracketed, sizeof(bracketed), "[ %s ]", timebuf);

    // 2) Obtiene TIPO => "ERR  :", "INFO :", etc.
    const char* type_str = get_type_suffix(type);

    // 3) Determina color
    const char* color = "";
    if (debug_colors_supported) {
        switch (type) {
            case DEBUG_INFO:  color = ANSI_FG_GREEN;   break;
            case DEBUG_WARN:  color = ANSI_FG_YELLOW;  break;
            case DEBUG_ERROR: color = ANSI_FG_RED;     break;
            case DEBUG_DEBUG: color = ANSI_FG_CYAN;    break;
            case DEBUG_FATAL: color = ANSI_FG_MAGENTA; break;
            default:          color = "";              break;
        }
    }

    // 4) prefix_plain (sin secuencias ANSI) => p.ej. "[   0.123456 ] ERR  : "
    char prefix_plain[256];
    snprintf(prefix_plain, sizeof(prefix_plain), "%s %s ", bracketed, type_str);
    int prefix_len = (int)strlen(prefix_plain);

    // 5) prefix_ansi => con color y bold en type, luego se retoma color normal
    //    para el resto del mensaje.
    char prefix_ansi[512];
    if (debug_colors_supported && *color) {
        // Ej: color + bracketed + " " + BOLD + type + RESET + color + " "
        snprintf(prefix_ansi, sizeof(prefix_ansi),
                 "%s%s %s%s%s%s ",
                 color, bracketed,
                 ANSI_BOLD, type_str,
                 ANSI_RESET, color);
    } else {
        // sin color
        snprintf(prefix_ansi, sizeof(prefix_ansi), "%s %s ", bracketed, type_str);
    }

    // 6) Imprimir el msg principal multiline
    print_multiline_msg(msg, prefix_ansi, prefix_len, color);

    // 7) Imprimir detail, alineado, en cursiva (y sin repetir prefix).
    print_detail(detail, prefix_len, color);
}
