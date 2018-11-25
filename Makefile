CC = cc
CFLAGS = -I$(IDIR) -ltcod

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