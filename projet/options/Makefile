
EXEC = main


CC = gcc


CFLAGS = -Wall -Wextra -g `sdl-config --cflags`
LDFLAGS = `sdl-config --libs` -lSDL_image -lSDL_mixer


SRC = main.c button.c
OBJ = $(SRC:.c=.o)

all: $(EXEC)


$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)


%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)


clean:
	rm -f $(OBJ) $(EXEC)


mrproper: clean
	rm -f *~ *.bak

