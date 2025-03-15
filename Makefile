CC = gcc

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

$(DEBUGDIR)/debug.o: $(DEBUGDIR)/debug.c
	$(CC) $(CFLAGS) -c $< -o $@

$(DEBUGDIR)/printer.o: $(DEBUGDIR)/printer.c
	$(CC) $(CFLAGS) -c $< -o $@

$(DEBUGDIR)/timer.o: $(DEBUGDIR)/timer.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
