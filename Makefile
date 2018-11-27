CC = cc
CFLAGS = -I$(IDIR) -ltcod -lm -std=c99 -pedantic -Wall

IDIR = ./include/
SRCDIR = ./src/

SOURCES = $(SRCDIR)*.c

all: crogue run clean

crogue:
	$(CC) $(SOURCES) $(CFLAGS) -o crogue

clean:
	rm crogue

run:
	./crogue
