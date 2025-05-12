#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include <stdio.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>

typedef struct
{
    SDL_Surface *backg;

    SDL_Surface *jouer_btn[2];
    SDL_Surface *option_btn[2];
    SDL_Surface *score_btn[2];
    SDL_Surface *hist_btn[2];
    SDL_Surface *quit_btn[2];
    SDL_Surface *reprendre_btn[2];
    SDL_Surface *logo;

    SDL_Rect pos_btn_jouer;
    SDL_Rect pos_btn_option;
    SDL_Rect pos_btn_score;
    SDL_Rect pos_btn_hist;
    SDL_Rect pos_btn_quit;
    SDL_Rect pos_btn_reprendre;
    SDL_Rect pos_logo;

    

    int btn_select;

    Mix_Music *bg_music;
    Mix_Chunk * son_click;

    SDL_Surface * Surface_Texte;
    SDL_Rect positiontext;
    TTF_Font *font;
    SDL_Color textColor;
}menu;


void init_menu(menu *m);
void afficher_menu(menu m,SDL_Surface *ecran,SDL_Event event);
int touche_souris(SDL_Rect pos_btn,SDL_Event event);
void mise_ajour_menu(menu *m,SDL_Event event);






#endif
