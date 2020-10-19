CC = gcc
CFLAGS = -lncurses -I$(IDIR)

IDIR = ./include/
SRCDIR = ./src/

SOURCES = $(SRCDIR)*.c

all: nethack run clean

nethack:
	$(CC) $(SOURCES) $(CFLAGS) -o $@

run:
	./nethack

clean:
	rm nethack