SHELL = /bin/sh
CC    = gcc
CFLAGS       = -fPIC -std=gnu99 -Iinclude  -pedantic -Wall -Wextra -march=native -ggdb3
LIB_LDFLAGS 	= -shared
LDFLAGS 	= -L./ -lsdmalloc -lpthread
DEBUGFLAGS   = -O0 -D _DEBUG
RELEASEFLAGS = -O2 -D NDEBUG -combine -fwhole-program

LIB_SO  = libsdmalloc.so
DAEMON  = sdmad
CLIENT    = sdmac 
DAEMON_SRC = src/sdmad.c
CLIENT_SRC = src/sdmac.c
SOURCES = src/sdmalloc.c
HEADERS = $(shell echo include/*.h)
OBJECTS = $(SOURCES:.c=.o)
DAEMON_OBJECTS = $(DAEMON_SRC:.c=.o)
CLIENT_OBJECTS = $(CLIENT_SRC:.c=.o)

PREFIX = $(DESTDIR)/usr/local
BINDIR = $(PREFIX)/bin

.PHONY: all
all: $(LIB_SO) $(DAEMON) $(CLIENT)

$(SOURCES:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< >$@

$(DAEMON_SRC:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< >$@

$(CLIENT_SRC:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< >$@

$(LIB_SO): $(OBJECTS)
	$(CC) $(CFLAGS) $(LIB_LDFLAGS) $(DEBUGFLAGS) -o $@ $^

$(DAEMON): $(DAEMON_OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(DEBUGFLAGS) -o $@ $^

$(CLIENT): $(CLIENT_OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(DEBUGFLAGS) -o $@ $^

.PHONY: clean
clean: 
	-rm -f $(LIB_SO) $(CLIENT_OBJECTS) $(DAEMON_OBJECTS) $(OBJECTS) $(DAEMON) $(CLIENT)

