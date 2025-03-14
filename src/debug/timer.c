#include "timer.h"

#if defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

static LARGE_INTEGER start_time, frequency;

void init_time() {
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start_time);
}

double get_elapsed_time() {
    LARGE_INTEGER now;
    QueryPerformanceCounter(&now);
    return (double)(now.QuadPart - start_time.QuadPart) / frequency.QuadPart;
}

#else // Linux, macOS

#include <time.h>

static struct timespec start_time;

void init_time() {
    clock_gettime(CLOCK_MONOTONIC, &start_time);
}

double get_elapsed_time() {
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    return (now.tv_sec - start_time.tv_sec)
         + (now.tv_nsec - start_time.tv_nsec) / 1e9;
}

#endif
