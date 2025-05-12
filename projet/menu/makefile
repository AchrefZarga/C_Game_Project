prog:menu.o main.o
	gcc  menu.o main.o -o prog -lSDL -g -lSDL_image -lSDL_mixer -lSDL_ttf
	rm -f *.o
main.o:main.c
	gcc -c main.c
menu.o:menu.c
	gcc -c menu.c
