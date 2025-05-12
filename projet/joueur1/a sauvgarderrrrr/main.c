#include "head.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>

int main() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        fprintf(stderr, "Erreur SDL_Init: %s\n", SDL_GetError());
        return 1;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1) {
        fprintf(stderr, "Erreur Mix_OpenAudio: %s\n", Mix_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Surface *ecran = SDL_SetVideoMode(1440, 900, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (!ecran) {
        fprintf(stderr, "Erreur SDL_SetVideoMode: %s\n", SDL_GetError());
        Mix_CloseAudio();
        SDL_Quit();
        return 1;
    }

    sous_menu_joueur sm;
    init_sous_menu_joueur(&sm);

    int quitter = 0;
    SDL_Event event;
    int indice_ecran = 0; // 0: menu principal, 1: sous-menu, 2: meilleurs scores

    while (!quitter) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quitter = 1;
            } else {
                switch (indice_ecran) {
                    case 0:
                        afficher_interface_principale(&sm, ecran, event, &indice_ecran, &quitter);
                        break;
                    case 1:
                        afficher_interface_secondaire(&sm, ecran, event, &indice_ecran, &quitter);
                        break;
                    case 2:
                        // Afficher le menu des meilleurs scores (à implémenter)
                        break;
                }
            }
        }
        SDL_Delay(10);
    }

    // Libération des ressources
    SDL_FreeSurface(sm.background);
    for (int i = 0; i < 2; i++) {
        SDL_FreeSurface(sm.mono_btn[i]);
        SDL_FreeSurface(sm.multi_btn[i]);
        SDL_FreeSurface(sm.retour_btn[i]);
        SDL_FreeSurface(sm.avatar1_btn[i]);
        SDL_FreeSurface(sm.avatar2_btn[i]);
        SDL_FreeSurface(sm.input1_btn[i]);
        SDL_FreeSurface(sm.input2_btn[i]);
        SDL_FreeSurface(sm.valider_btn[i]);
        SDL_FreeSurface(sm.retrn_btn[i]);
    }
    Mix_FreeMusic(sm.bg_music);
    Mix_FreeChunk(sm.hover_sound);
    Mix_CloseAudio();
    SDL_Quit();

    return 0;
}
