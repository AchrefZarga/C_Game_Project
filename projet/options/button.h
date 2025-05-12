#ifndef BUTTON_H
#define BUTTON_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>

/* Définition de la structure Button */
typedef struct {
    SDL_Surface *normal;
    SDL_Surface *hover;
    int x, y;
} Button;

/* Déclaration des fonctions */
void initButton(Button *btn, const char *normalPath, const char *hoverPath, int x, int y);
void renderButton(SDL_Surface *screen, Button btn, int isHover);
void freeButton(Button *btn);

#endif // BUTTON_H

