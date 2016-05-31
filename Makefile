SHELL = /bin/sh
CC    = gcc
CFLAGS       = -fPIC -std=gnu99 -Iinclude  -pedantic -Wall -Wextra -march=native -ggdb3
LDFLAGS 	= -shared
DEBUGFLAGS   = -O0 -D _DEBUG
RELEASEFLAGS = -O2 -D NDEBUG -combine -fwhole-program

TARGET  = libsdmalloc.so
SOURCES = $(shell echo src/*.c)
HEADERS = $(shell echo include/*.h)
OBJECTS = $(SOURCES:.c=.o)

PREFIX = $(DESTDIR)/usr/local
BINDIR = $(PREFIX)/bin

.PHONY: all
all: $(TARGET)

$(SOURCES:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< >$@

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(DEBUGFLAGS) -o $@ $^

.PHONY: clean
clean: 
	-rm $(TARGET) $(OBJECTS)

