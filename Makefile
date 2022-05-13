CC=gcc
LIBS=$(shell sdl2-config --libs) -lm
FLAGS=$(shell sdl2-config --cflags) -W -Wall -g
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

mrproper : clean
	rm -rf $(EXEC)

# $@ ref cible
# $< ref premiere dependance
# $^ ref listes dependances

# main.o : main.cpp
# 	$(CC) -c main.cpp
