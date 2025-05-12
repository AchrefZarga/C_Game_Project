#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "enigme2.h"

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Surface* ecran = SDL_SetVideoMode(1440, 700, 32, SDL_HWSURFACE);
    if (!ecran) {
        printf("Erreur d'initialisation de la fenêtre : %s\n", SDL_GetError());
        return 1;
    }

    Enigme2 enigme2;
    init_bg(&enigme2);

    int quitter = 0;
    SDL_Event event;

    while (!quitter) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quitter = 1;
            }
            clickButton(&enigme2, event);
        }

        afficher_bg(enigme2, ecran);
        mettre_a_jour_enigme(&enigme2);

        if (enigme2.jouer_gagner == 0) {
            quitter = 1;
            liberer_enigme(&enigme2);
        }

        SDL_Flip(ecran);
    }

    SDL_Quit();
    return 0;
}
