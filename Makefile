CXX=gcc
LIBS=$(shell sdl2-config --libs) -lm
FLAGS=$(shell sdl2-config --cflags) -W -Wall
SRC=$(wildcard src/*.c)
OBJ=$(SRC:.c=.o)
EXEC=graviter

all : $(EXEC)

$(EXEC) : $(OBJ)
	$(CXX) $^ -o $@ $(LIBS)

%.o : %.c
	$(CXX) -c $< -o $@ $(FLAGS)

clean :
	rm -rf src/*.o

mrproper : clean
	rm -rf $(EXEC)

# $@ ref cible
# $< ref premiere dependance
# $^ ref listes dependances

# main.o : main.cpp
# 	$(CXX) -c main.cpp
