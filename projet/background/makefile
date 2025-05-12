# Variables
CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -lSDL -lSDL_ttf -lSDL_image -lSDL_mixer
SRC = main.c background.c menu.c # Ajoutez ici tous les fichiers sources de votre projet
OBJ = $(SRC:.c=.o)
EXEC = jeu

# Cibles
all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $(EXEC) $(OBJ) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)

run: $(EXEC)
	./$(EXEC)

.PHONY: all clean run

