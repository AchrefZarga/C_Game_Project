#include "button.h"
#include <stdio.h>

/* Fonction d'initialisation d'un bouton */
void initButton(Button *btn, const char *normalPath, const char *hoverPath, int x, int y) {
    btn->normal = IMG_Load(normalPath);
    if (!btn->normal) {
        printf("Erreur chargement de l'image normale (%s) : %s\n", normalPath, IMG_GetError());
    }
    btn->hover = IMG_Load(hoverPath);
    if (!btn->hover) {
        printf("Erreur chargement de l'image hover (%s) : %s\n", hoverPath, IMG_GetError());
    }
    btn->x = x;
    btn->y = y;
}

/* Fonction de rendu d'un bouton */
void renderButton(SDL_Surface *screen, Button btn, int isHover) {
    SDL_Rect pos = { btn.x, btn.y, 0, 0 };
    if (isHover && btn.hover) {
        SDL_BlitSurface(btn.hover, NULL, screen, &pos);
    } else if (btn.normal) {
        SDL_BlitSurface(btn.normal, NULL, screen, &pos);
    }
}

/* Libération des ressources d'un bouton */
void freeButton(Button *btn) {
    if (btn->normal) SDL_FreeSurface(btn->normal);
    if (btn->hover) SDL_FreeSurface(btn->hover);
}

