#ifndef BACKGROUND_H
#define BACKGROUND_H
#include <SDL/SDL_ttf.h>
#include <SDL/SDL.h>
#include <stdbool.h>

typedef struct {
    SDL_Surface *image;
    SDL_Rect camera1, camera2;
} Background;

void initBackground(Background *bg, const char *path);
void displayBackground(Background *bg, SDL_Surface *screen);
void scrollBackground(Background *bg, int dx, int dy, bool player1);
void freeBackground(Background *bg);
void afficherFenetreGuide(SDL_Surface *screen, TTF_Font *font, SDL_Color color);

#endif

