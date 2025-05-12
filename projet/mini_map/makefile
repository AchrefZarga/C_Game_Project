# Makefile pour projet SDL 1.2 avec SDL_image et SDL_mixer

CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -lSDL -lSDL_image -lSDL_mixer

SRC = main.c mini_map.c
OBJ = $(SRC:.c=.o)
EXEC = jeu

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) $(LDFLAGS)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f *.o $(EXEC)

run: all
	./$(EXEC)

