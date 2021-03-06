.PHONY= clean

CC=g++
OPTIONS= -g -Wall -O2
DEBUG= #-D DEBUG
LIBDIR=src
INCLUDEDIR=include
_OBJ= Sonido.o Pieza.o Puzzle.o Directorio.o Juego_EstadoMenu.o Juego_EstadoJugando.o Juego.o
OBJ = $(patsubst %,$(LIBDIR)/%,$(_OBJ))

all: main

main: ./main.cpp $(OBJ)
	$(CC) $(OPTIONS) $(DEBUG) -I$(INCLUDEDIR) -lSDL -lSDL_ttf -lSDL_mixer -lSDL_image -lpthread -I/usr/include/SDL -D_REENTRANT ./main.cpp $(OBJ) -o main

$(LIBDIR)/%.o : $(LIBDIR)/%.cpp $(INCLUDEDIR)/%.h
	$(CC) $(OPTIONS) $(DEBUG) -c -I$(INCLUDEDIR) -I/usr/include/SDL -D_REENTRANT -o $@ $<

clean:
	rm -f $(OBJ)
	rm -f main
