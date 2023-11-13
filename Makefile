
PREFIX ?= /usr/local
BINDIR = $(PREFIX)/bin
TARGET = tcat
LIBS = -lm
CFLAGS = -D_POSIX_C_SOURCE=200112L -std=c99 -Wall -Wextra -Werror -Os

.PHONY: default all clean install uninstall

default: $(TARGET)
all: default

OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
HEADERS = $(wildcard *.h)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall $(LIBS) -o $@

clean:
	-rm -f *.o
	-rm -f $(TARGET)

install: $(TARGET)
	cp -f $(TARGET) $(BINDIR)/$(TARGET)

uninstall:
	rm -f $(BINDIR)/$(TARGET)
