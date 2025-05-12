#ifndef ENEMY_H
#define ENEMY_H



#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <SDL/SDL_ttf.h>



#define FRAME_COUNT 6
#define DETECTION_RANGE 200
#define ATTAQUE_RANGE 50
#define VIE_MAX 100



typedef struct {
    SDL_Surface *spriteSheet;
    SDL_Rect frameRects[18];
    SDL_Rect position;
    int niveau;
    int etat;
    double vitesse, acceleration;
    int frameIndex;
    int vie;
    int direction;
    int posMinX, posMaxX, posMinY, posMaxY;
    Uint32 dernierTir;
    Uint32 lastAnimTime;
} Ennemie;



typedef struct {
    SDL_Surface *image;
    SDL_Rect position;
    int actif;
    int vitesse;
    int direction;
} Projectile;



typedef enum {
    SOL,
    OBSTACLE,
    PIEGE,
    BONUS
} TypeSurface;



typedef struct {
    SDL_Surface *image;
    SDL_Rect position;
    int actif;
} Bonus;


void initialiserBonus(Bonus pommes[], SDL_Surface *imageBonus1, SDL_Surface *imageBonus2);
void afficherBonus(Bonus pommes[], int nb, SDL_Surface *ecran);



SDL_Color GetPixel(SDL_Surface *surface, int x, int y);
int CollisionParfaite(SDL_Surface *backgroundMasque, SDL_Rect perso);
int collisionTrigonometrie(SDL_Rect a, SDL_Rect b);
TypeSurface VerifierTypeSurface(SDL_Surface *masque, SDL_Rect position);
void initialiserEnnemie(Ennemie *e, int niveau, int index);



void afficherEnnemie(Ennemie e, SDL_Surface *ecran);
void deplacerEnnemie(Ennemie *e, SDL_Rect joueurPos, SDL_Surface *backgroundMasque, Bonus pommes[], int nbPommes);
void animerEnnemie(Ennemie *e);
void gererAttaqueEnnemie(Ennemie *e, SDL_Rect joueurPos, Projectile *projectiles);
void gererEtatEnnemie(Ennemie *e, int etat);
void afficherEtatEnnemie(Ennemie e, SDL_Surface *ecran);
void initialiserProjectile(Projectile *p, int niveau);
void gererProjectiles(Projectile *p, SDL_Surface *ecran, SDL_Surface *backgroundMasque, SDL_Rect joueurPos);



#endif
