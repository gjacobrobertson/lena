CC = g++ -c
CFLAGS =  `pkg-config --cflags opencv`

LINKER = g++
LFLAGS =  `pkg-config --libs opencv`

SRCDIR = src
OBJDIR = obj
BINDIR = bin

ALL = $(BINDIR)/warhol

all: $(ALL)

$(BINDIR)/warhol: $(OBJDIR)/warhol.o
	$(LINKER) $(LFLAGS) $(OBJDIR)/warhol.o -o $(BINDIR)/warhol

$(OBJDIR)/warhol.o: $(SRCDIR)/warhol.cpp
	$(CC) $(CFLAGS) $(SRCDIR)/warhol.cpp -o $(OBJDIR)/warhol.o

clean:
	rm -rf obj/* bin/*
