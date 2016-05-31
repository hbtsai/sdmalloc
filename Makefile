SHELL = /bin/sh
CC    = gcc
CFLAGS       = -fPIC -std=gnu99 -Iinclude  -pedantic -Wall -Wextra -march=native -ggdb3
LIB_LDFLAGS 	= -shared
LDFLAGS 	= -L./ -lsdmalloc
DEBUGFLAGS   = -O0 -D _DEBUG
RELEASEFLAGS = -O2 -D NDEBUG -combine -fwhole-program

LIB_SO  = libsdmalloc.so
DAEMON  = sdmad
SOURCES = $(shell echo src/*.c)
HEADERS = $(shell echo include/*.h)
OBJECTS = $(SOURCES:.c=.o)

PREFIX = $(DESTDIR)/usr/local
BINDIR = $(PREFIX)/bin

.PHONY: all
all: $(LIB_SO) $(DAEMON)

$(SOURCES:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< >$@

$(LIB_SO): $(OBJECTS)
	$(CC) $(CFLAGS) $(LIB_LDFLAGS) $(DEBUGFLAGS) -o $@ $^

$(DAEMON): $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(DEBUGFLAGS) -o $@ $^


.PHONY: clean
clean: 
	-rm $(LIB_SO) $(OBJECTS)

