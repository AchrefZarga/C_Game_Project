#ifndef JOUEUR_H
#define JOUEUR_H

#include <SDL/SDL.h>
#include <stdbool.h>
#define LARGEUR_FRAME 140
#define HAUTEUR_FRAME 200
#define NB_FRAMES 6

typedef enum {
    ANIM_IDLE,
    ANIM_MARCHE,
    ANIM_SAUT,
    ANIM_ATTAQUE,
    ANIM_MORT,
    ANIM_GAGNER,
} TypeAnimation;

typedef struct {
    SDL_Surface* spriteSheet;
    SDL_Rect positionEcran;
    SDL_Rect frameActuel;
    TypeAnimation animation;
    int direction; // 0: droite, 1: gauche
    int frameIndex;
    Uint32 derniereAnimation;
    int vies;
    int score;
    bool estActif;
    bool auSol;
    bool enSaut;
     SDL_Surface *coeurs[3];
} Joueur;

void initJoueur(Joueur* j, const char* spritePath, int x, int y);
void animerJoueur(Joueur* j);
void changerAnimation(Joueur* j, TypeAnimation nouvelleAnim);
void reduireVies(Joueur* j, int montant);
void handleEvent(Joueur* j, SDL_Event* event);
void dessinerJoueur(SDL_Surface* ecran, Joueur* j);
void libererJoueur(Joueur* j);
void initCoeurs(Joueur* j);
void afficherVies(SDL_Surface* ecran, Joueur* j, int xDepart);
void gererScore(SDL_Surface* ecran, int score, int xDepart) ;
void handleEventJoueur2(Joueur* joueur, SDL_Event* event);


#endif // JOUEUR_H

