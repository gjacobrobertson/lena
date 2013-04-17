CC = g++ -c
CFLAGS =  `pkg-config --cflags opencv`

LINKER = g++
LFLAGS =  `pkg-config --libs opencv`

SRCDIR = src
OBJDIR = obj
BINDIR = bin

ALL = $(BINDIR)/warhol $(BINDIR)/contour

all: $(ALL)

$(BINDIR)/warhol: $(OBJDIR)/warhol.o
	$(LINKER) $(LFLAGS) $(OBJDIR)/warhol.o -o $(BINDIR)/warhol

$(OBJDIR)/warhol.o: $(SRCDIR)/warhol.cpp
	$(CC) $(CFLAGS) $(SRCDIR)/warhol.cpp -o $(OBJDIR)/warhol.o

$(BINDIR)/contour: $(OBJDIR)/contour.o
	$(LINKER) $(LFLAGS) $(OBJDIR)/contour.o -o $(BINDIR)/contour

$(OBJDIR)/contour.o: $(SRCDIR)/contour.cpp
	$(CC) $(CFLAGS) $(SRCDIR)/contour.cpp -o $(OBJDIR)/contour.o

clean:
	rm -rf obj/* bin/*
