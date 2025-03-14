CC = gcc

# Para Windows se puede usar -D_CRT_SECURE_NO_WARNINGS
# Para Linux/macOS se habilita -D_POSIX_C_SOURCE=200809L
# En la práctica, si compilas en Windows con MinGW, `_POSIX_C_SOURCE` no le afecta,
# pero no molesta. También es posible usar un #ifdef en el Makefile, pero para
# simplificar, lo dejamos así.
CFLAGS = -Wall -Wextra -std=c99 -D_POSIX_C_SOURCE=200809L -D_CRT_SECURE_NO_WARNINGS

SRCDIR = src
FIBDIR = $(SRCDIR)/fibonacci
DEBUGDIR = $(SRCDIR)/debug

OBJS = \
	$(SRCDIR)/main.o \
	$(FIBDIR)/fibonacci.o \
	$(DEBUGDIR)/debug.o \
	$(DEBUGDIR)/printer.o \
	$(DEBUGDIR)/timer.o

TARGET = binary

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(SRCDIR)/main.o: $(SRCDIR)/main.c
	$(CC) $(CFLAGS) -c $< -o $@

$(FIBDIR)/fibonacci.o: $(FIBDIR)/fibonacci.c
	$(CC) $(CFLAGS) -c $< -o $@

$(DEBUGDIR)/debug.o: $(DEBUGDIR)/debug.c
	$(CC) $(CFLAGS) -c $< -o $@

$(DEBUGDIR)/printer.o: $(DEBUGDIR)/printer.c
	$(CC) $(CFLAGS) -c $< -o $@

$(DEBUGDIR)/timer.o: $(DEBUGDIR)/timer.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
