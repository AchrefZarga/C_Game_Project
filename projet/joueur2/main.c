#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdio.h>
#include "joueur.h"
#include <SDL/SDL_ttf.h>

#define SCREEN_WIDTH 1440
#define SCREEN_HEIGHT 700

SDL_Surface* chargerBackground(const char* chemin) {
    SDL_Surface* temp = IMG_Load(chemin);
    if (!temp) {
        fprintf(stderr, "Erreur chargement background : %s\n", IMG_GetError());
        return NULL;
    }
    SDL_Surface* bg = SDL_DisplayFormat(temp);
    SDL_FreeSurface(temp);
    return bg;
}

void verifierCollisionMasque(Joueur* joueur, SDL_Surface* bgCollision, Uint32 couleurVert, Uint32 couleurNoire) {
    SDL_LockSurface(bgCollision);
    Uint32* pixels = (Uint32*)bgCollision->pixels;
    int pitch = bgCollision->pitch / 4;

    SDL_Rect pos = joueur->positionEcran;
    joueur->auSol = false;

    for (int y = pos.y; y < pos.y + pos.h; y++) {
        for (int x = pos.x; x < pos.x + pos.w; x++) {
            Uint32 couleur = pixels[y * pitch + x];
            if (couleur == couleurVert) {
                reduireVies(joueur, 1); // Réduire la vie en cas de collision avec un obstacle vert
            } else if (couleur == couleurNoire && y == pos.y + pos.h - 1) {
                joueur->auSol = true; // Le joueur est sur le sol marchable
            }
        }
    }

    SDL_UnlockSurface(bgCollision);

    if (!joueur->auSol) {
        joueur->positionEcran.y += 10; // Appliquer la gravité
        if (joueur->positionEcran.y >= SCREEN_HEIGHT - joueur->positionEcran.h) {
            joueur->positionEcran.y = SCREEN_HEIGHT - joueur->positionEcran.h;
            joueur->auSol = true;
        }
    }
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Erreur SDL : %s\n", SDL_GetError());
        return 1;
    }

    if (TTF_Init() == -1) {
        fprintf(stderr, "Erreur SDL_ttf : %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Surface* ecran = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_HWSURFACE);
    if (!ecran) {
        fprintf(stderr, "Erreur création écran : %s\n", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_WM_SetCaption("Exemple SDL", NULL);

    SDL_Surface* bgNormal = chargerBackground("background_normal.jpg");
    SDL_Surface* bgCollision = chargerBackground("background_mask.png");

    if (!bgNormal || !bgCollision) {
        if (bgNormal) SDL_FreeSurface(bgNormal);
        if (bgCollision) SDL_FreeSurface(bgCollision);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    Joueur joueur;
    initJoueur(&joueur, "44.png", 100, 400);
    Joueur joueur2;
    initJoueur(&joueur2, "55.png", 70, 400);

    joueur.direction = -1;
    joueur2.direction = -1;  // Aucun mouvement au démarrage
    changerAnimation(&joueur, ANIM_IDLE); // Animation "Idle"

    Uint32 couleurVert = SDL_MapRGB(bgCollision->format, 35, 177, 77);
    Uint32 couleurNoire = SDL_MapRGB(bgCollision->format, 0, 0, 0);
    int score = 0;
    bool continuer = true;
    SDL_Event event;

while (continuer) {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            continuer = false;
        } else if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
            handleEvent(&joueur, &event);  // Joueur 1
            handleEventJoueur2(&joueur2, &event);  // Joueur 2
        }
    }

    // Déplacement continu du joueur en fonction de la direction
    if (joueur.animation != ANIM_MORT) {
        if (joueur.direction == 1) {
            joueur.positionEcran.x -= 10;  // Déplacer vers la gauche
        } else if (joueur.direction == 0) {
            joueur.positionEcran.x += 10;  // Déplacer vers la droite
        }
    }

    if (joueur2.animation != ANIM_MORT) {
        if (joueur2.direction == 1) {
            joueur2.positionEcran.x -= 10;  // Déplacer vers la gauche
        } else if (joueur2.direction == 0) {
            joueur2.positionEcran.x += 10;  // Déplacer vers la droite
        }
    }

    verifierCollisionMasque(&joueur, bgCollision, couleurVert, couleurNoire);
    verifierCollisionMasque(&joueur2, bgCollision, couleurVert, couleurNoire);

    SDL_BlitSurface(bgNormal, NULL, ecran, NULL);
    animerJoueur(&joueur);
    dessinerJoueur(ecran, &joueur);
    afficherVies(ecran, &joueur2, 700);
    afficherVies(ecran, &joueur, 10);
    gererScore(ecran, score, 10);
    gererScore(ecran, joueur2.score, 700);
    animerJoueur(&joueur2);
    dessinerJoueur(ecran, &joueur2);

    SDL_Flip(ecran);
    SDL_Delay(16);  // Attente pour contrôler la vitesse du jeu
}


    SDL_FreeSurface(bgNormal);
    SDL_FreeSurface(bgCollision);
    TTF_Quit();
    SDL_Quit();
    return 0;
}

