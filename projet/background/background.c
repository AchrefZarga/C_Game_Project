#include "background.h"
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>

void initBackground(Background *bg, const char *path) {
    bg->image = IMG_Load(path);
    if (!bg->image) {
        printf("Erreur chargement background : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    bg->camera1 = (SDL_Rect){0, 0, 1440, 700};
    bg->camera2 = (SDL_Rect){0, 0, 720, 700};
}

void displayBackground(Background *bg, SDL_Surface *screen) {
    SDL_Rect pos1 = {0, 0};
    SDL_Rect pos2 = {720, 0};

    SDL_BlitSurface(bg->image, &bg->camera1, screen, &pos1);
    SDL_BlitSurface(bg->image, &bg->camera2, screen, &pos2);
}

void scrollBackground(Background *bg, int dx, int dy, bool player1) {
    SDL_Rect *cam = player1 ? &bg->camera1 : &bg->camera2;
    cam->x += dx;
    cam->y += dy;

    if (cam->x < 0) cam->x = 0;
    if (cam->y < 0) cam->y = 0;
    if (cam->x > bg->image->w - cam->w) cam->x = bg->image->w - cam->w;
    if (cam->y > bg->image->h - cam->h) cam->y = bg->image->h - cam->h;
}

void afficherFenetreGuide(SDL_Surface *screen, TTF_Font *font, SDL_Color color) {
    SDL_Rect rect = {100, 100, 600, 400};
    SDL_FillRect(screen, &rect, SDL_MapRGB(screen->format, 0, 0, 0));

    const char *messages[3] = {
        "Bienvenue dans le jeu!",
        "Utilisez les fleches pour deplacer.",
        "Appuyez sur Echap pour quitter."
    };

    for (int i = 0; i < 3; i++) {
        SDL_Surface *textSurface = TTF_RenderText_Solid(font, messages[i], color);
        SDL_Rect textPosition = {120, 120 + i * 50};
        SDL_BlitSurface(textSurface, NULL, screen, &textPosition);
        SDL_FreeSurface(textSurface);
    }

    SDL_Flip(screen);
}

void freeBackground(Background *bg) {
    SDL_FreeSurface(bg->image);
}

