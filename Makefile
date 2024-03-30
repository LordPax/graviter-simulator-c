# $@ ref cible
# $< ref premiere dependance
# $^ ref listes dependances

CC=gcc
# LIBS=$(shell sdl2-config --libs) -lSDL2_ttf -lm
# FLAGS=$(shell sdl2-config --cflags) -W -Wall -g
LIBS=-L /usr/lib -l SDL2 -l SDL2_ttf -lm
FLAGS=-I /usr/include/SDL2 -D_REENTRANT -W -Wall -g
SRC=$(wildcard src/*.c)
OBJ=$(SRC:.c=.o)
EXEC=graviter

all : $(EXEC)

$(EXEC) : $(OBJ)
	$(CC) $^ -o $@ $(LIBS)

%.o : %.c
	$(CC) -c $< -o $@ $(FLAGS)

clean :
	rm -rf src/*.o

cleanall : clean
	rm -rf $(EXEC)
