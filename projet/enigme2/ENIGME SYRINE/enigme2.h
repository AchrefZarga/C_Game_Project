#ifndef ENIGME2_H
#define ENIGME2_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>

typedef struct {
    SDL_Surface *bkg;                          
    SDL_Surface *puzzle[11];  

    SDL_Rect pos_btn_puzzle[11]; 
    SDL_Rect pos_correcte[11];   
    SDL_Rect pos_initiale[11];   
    int piece_placee[11];       

    //timer
    SDL_Surface *timer[61];
    SDL_Rect pos_timer;
    int compteur;
    int temps_start_jouer;

    int jouer_gagner;
} Enigme2;

void init_bg(Enigme2 *bg);
void afficher_bg(Enigme2 bg, SDL_Surface *ecran);
void clickButton(Enigme2 *bg, SDL_Event event);
void mettre_a_jour_enigme(Enigme2 *e);
void liberer_enigme(Enigme2 *e);
#endif
