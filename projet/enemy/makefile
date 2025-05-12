prog: enemy.o main.o
	gcc enemy.o main.o -o prog -lSDL -g -lSDL_image -lSDL_mixer -lSDL_ttf -lm
	rm -f *.o

main.o: main.c
	gcc -c main.c

enemy.o: enemy.c
	gcc -c enemy.c

