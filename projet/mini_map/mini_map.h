#ifndef FONCTION_H
#define FONCTION_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#define PLAYER_RADIUS 10

extern SDL_Surface *background, *minimap, *backgroundMask;

typedef struct {
    int x, y;
    int taille;
    int direction;
    SDL_Color color;
    Uint32 lastUpdate;
    int frameDelay;
    int animating;
    int colorPhase;
} Player;

void chargerArrierePlans();
SDL_Surface* load_image(const char *filename);
void animer_joueur(Player *p);
void draw_player(SDL_Surface *screen, Player *p);
void draw_minimap(SDL_Surface *screen, SDL_Surface *minimap, int player_x, int player_y, SDL_Rect camera);
int CollisionParfaite(SDL_Surface *mask, int x, int y, int w, int h);
int collision_AABB(SDL_Rect rect1, SDL_Rect rect2);
Uint32 GetPixel(SDL_Surface *surface, int x, int y);

#endif
