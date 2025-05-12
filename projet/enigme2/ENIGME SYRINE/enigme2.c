#include "enigme2.h"
#include <stdio.h>
#include <SDL/SDL_image.h>
#include <math.h>

void init_bg(Enigme2 *bg) {
    bg->bkg = IMG_Load("images/abstract-textured-backgound.jpg");
    if (bg->bkg == NULL) {
        printf("Erreur de chargement de l'image bg.png: %s\n", IMG_GetError());
    }
    bg->puzzle[0] = IMG_Load("images/p1.png");
    bg->puzzle[1] = IMG_Load("images/p2.png");
    bg->puzzle[2] = IMG_Load("images/p3.png");
    bg->puzzle[3] = IMG_Load("images/p4.png");
    bg->puzzle[4] = IMG_Load("images/p5.png");
    bg->puzzle[5] = IMG_Load("images/p6.png");
    bg->puzzle[6] = IMG_Load("images/p7.png");
    bg->puzzle[7] = IMG_Load("images/p8.png");
    bg->puzzle[8] = IMG_Load("images/p9.png");
    bg->puzzle[9] = IMG_Load("images/p5.3.png");
    bg->puzzle[10] = IMG_Load("images/p5.2.png");
    bg->pos_btn_puzzle[0].x = 100;
    bg->pos_btn_puzzle[0].y = 140;
    bg->pos_btn_puzzle[0].w = bg->puzzle[0]->w;
    bg->pos_btn_puzzle[0].h = bg->puzzle[0]->h;
    bg->pos_btn_puzzle[1].x = 277;
    bg->pos_btn_puzzle[1].y = 135;
    bg->pos_btn_puzzle[1].w = bg->puzzle[1]->w;
    bg->pos_btn_puzzle[1].h = bg->puzzle[1]->h;
    bg->pos_btn_puzzle[2].x = 492;
    bg->pos_btn_puzzle[2].y = 147;
    bg->pos_btn_puzzle[2].w = bg->puzzle[2]->w;
    bg->pos_btn_puzzle[2].h = bg->puzzle[2]->h;
    bg->pos_btn_puzzle[3].x = 142;
    bg->pos_btn_puzzle[3].y = 317;
    bg->pos_btn_puzzle[3].w = bg->puzzle[3]->w;
    bg->pos_btn_puzzle[3].h = bg->puzzle[3]->h;
    bg->pos_btn_puzzle[4].x = 1000;
    bg->pos_btn_puzzle[4].y = 40; 
    bg->pos_btn_puzzle[4].w = bg->puzzle[4]->w;
    bg->pos_btn_puzzle[4].h = bg->puzzle[4]->h;
    bg->pos_btn_puzzle[5].x = 460;
    bg->pos_btn_puzzle[5].y = 316;
    bg->pos_btn_puzzle[5].w = bg->puzzle[5]->w;
    bg->pos_btn_puzzle[5].h = bg->puzzle[5]->h;
    bg->pos_btn_puzzle[6].x = 102;
    bg->pos_btn_puzzle[6].y = 484;
    bg->pos_btn_puzzle[6].w = bg->puzzle[6]->w;
    bg->pos_btn_puzzle[6].h = bg->puzzle[6]->h;
    bg->pos_btn_puzzle[7].x = 248;
    bg->pos_btn_puzzle[7].y = 490;
    bg->pos_btn_puzzle[7].w = bg->puzzle[7]->w;
    bg->pos_btn_puzzle[7].h = bg->puzzle[7]->h;
    bg->pos_btn_puzzle[8].x = 437;
    bg->pos_btn_puzzle[8].y = 480;
    bg->pos_btn_puzzle[8].w = bg->puzzle[8]->w;
    bg->pos_btn_puzzle[8].h = bg->puzzle[8]->h;
    bg->pos_btn_puzzle[9].x = 1000;
    bg->pos_btn_puzzle[9].y = 330;
    bg->pos_btn_puzzle[9].w = bg->puzzle[9]->w;
    bg->pos_btn_puzzle[9].h = bg->puzzle[9]->h;
    bg->pos_btn_puzzle[10].x = 1000;
    bg->pos_btn_puzzle[10].y = 550;
    bg->pos_btn_puzzle[10].w = bg->puzzle[10]->w;
    bg->pos_btn_puzzle[10].h = bg->puzzle[10]->h;
    for(int i=0;i<61;i++){
        char nom_fichier[50];
        sprintf(nom_fichier, "images/timer/timer_%d.png", i+1);
        bg->timer[i] = IMG_Load(nom_fichier);
    }
    bg->pos_timer.x = 600;
    bg->pos_timer.y = -10;
    bg->compteur = 1;
    bg->temps_start_jouer = SDL_GetTicks();
    bg->jouer_gagner = -1;
}
void afficher_bg(Enigme2 bg, SDL_Surface *ecran) {
    SDL_BlitSurface(bg.bkg, NULL, ecran, NULL);
    for (int i = 0; i < 11; i++) {
        SDL_BlitSurface(bg.puzzle[i], NULL, ecran, &bg.pos_btn_puzzle[i]);
    }
    SDL_BlitSurface(bg.timer[bg.compteur],NULL,ecran,&bg.pos_timer);
}
void clickButton(Enigme2 *bg, SDL_Event event) {
    static int pieceSelectionnee = -1;
    static int offsetX = 0, offsetY = 0;
    static SDL_Rect posInitiale[11];
    static int positionsSauvegardees = 0;
    if (!positionsSauvegardees) {  
        for (int i = 0; i < 11; i++) {
            posInitiale[i] = bg->pos_btn_puzzle[i];
        }
        positionsSauvegardees = 1;
    }

    if (event.type == SDL_MOUSEBUTTONDOWN) { 
        for (int i = 4; i <= 10; i++) {  
            if (event.button.x >= bg->pos_btn_puzzle[i].x &&
                event.button.x <= bg->pos_btn_puzzle[i].x + bg->puzzle[i]->w &&
                event.button.y >= bg->pos_btn_puzzle[i].y &&
                event.button.y <= bg->pos_btn_puzzle[i].y + bg->puzzle[i]->h) {
                
                pieceSelectionnee = i;
                offsetX = event.button.x - bg->pos_btn_puzzle[i].x;
                offsetY = event.button.y - bg->pos_btn_puzzle[i].y;
                break;
            }
        }
    }

    if (event.type == SDL_MOUSEMOTION && pieceSelectionnee != -1) {
        bg->pos_btn_puzzle[pieceSelectionnee].x = event.motion.x - offsetX;
        bg->pos_btn_puzzle[pieceSelectionnee].y = event.motion.y - offsetY;
    }

    if (event.type == SDL_MOUSEBUTTONUP && pieceSelectionnee != -1) {
        SDL_Rect posCorrecte = {270, 300, 0, 0};
        SDL_Rect *posActuelle = &bg->pos_btn_puzzle[pieceSelectionnee];

        if (pieceSelectionnee == 4) {  
            if (abs(posActuelle->x - posCorrecte.x) < 70 && abs(posActuelle->y - posCorrecte.y) < 70) {
                posActuelle->x = posCorrecte.x;
                posActuelle->y = posCorrecte.y;
                bg->piece_placee[pieceSelectionnee] = 1;
                bg->jouer_gagner = 1;  
            } else { 
                *posActuelle = posInitiale[pieceSelectionnee];  
            }
        } else { 
            *posActuelle = posInitiale[pieceSelectionnee];  
        }

        pieceSelectionnee = -1;
    }
}

void mettre_a_jour_enigme(Enigme2 *e) {
    if (e->jouer_gagner == 1) {
        return;
    }
    if (SDL_GetTicks() - e->temps_start_jouer >= 1000) {
        if (e->compteur < 60)
            e->compteur++;
        else {
            printf("you lose \n");
            e->jouer_gagner = 0;
        }

        e->temps_start_jouer = SDL_GetTicks();
    }
}

void liberer_enigme(Enigme2 *e) {
    SDL_FreeSurface(e->bkg);
    for (int i = 0; i < 11; i++) {
        SDL_FreeSurface(e->puzzle[i]);
    }
    for (int i = 0; i < 61; i++) {
        SDL_FreeSurface(e->timer[i]);
    }
}
