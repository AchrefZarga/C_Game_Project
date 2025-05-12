#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include "button.h"
#include <unistd.h>

int main() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf("Erreur SDL : %s\n", SDL_GetError());
        return 1;
    }
    int imgFlags = IMG_INIT_PNG;
if (!(IMG_Init(imgFlags) & imgFlags)) {
    printf("Erreur initialisation SDL_image : %s\n", IMG_GetError());
}

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("Erreur Mix_OpenAudio : %s\n", Mix_GetError());
        return 1;
    }

    Mix_Music *music = Mix_LoadMUS("Opening Credits  Game of Thrones  Season 8 (HBO).mp3");
    if (!music) {
        printf("Erreur chargement musique : %s\n", Mix_GetError());
    } else {
        Mix_PlayMusic(music, -1);
    }

    SDL_Surface *screen = SDL_SetVideoMode(1440, 900, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (!screen) {
        printf("Erreur création fenêtre : %s\n", SDL_GetError());
        return 1;
    }
    if (access("background.png", F_OK) != 0) {
    perror("background.png non trouvé");
}

    SDL_Surface *background = IMG_Load("background.png");
    if (!background) {
        printf("Erreur chargement background : %s\n", IMG_GetError());
        return 1;
    }

   

    Button diminuer, augmenter, normal, plein_d_ecran, retour;
    initButton(&diminuer, "Fichier 11diminuer.png", "diminuer.png", 585, 140);
    initButton(&augmenter, "Fichier 12augmenter.png", "augmenter.png", 900, 140);
    initButton(&normal, "Fichier 13normal.png", "Fichier 18norma2 .png", 585, 250);
    initButton(&plein_d_ecran, "Fichier 14pleainecran.png", "pleinecran.png", 900, 250);
    initButton(&retour, "retour2.png", "retour.png", 950, 600);

    int running = 1;
    int hover[5] = {0};
    SDL_Event event;
    const int volumeStep = 16;

    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = 0;
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                        running = 0;
                    break;
                case SDL_MOUSEMOTION:
                    hover[0] = (event.motion.x > 603 && event.motion.x < 855 && event.motion.y > 256 && event.motion.y < 321);
                    hover[1] = (event.motion.x > 917 && event.motion.x < 1170 && event.motion.y > 253 && event.motion.y < 322);
                    hover[2] = (event.motion.x > 603 && event.motion.x < 858 && event.motion.y > 367 && event.motion.y < 430);
                    hover[3] = (event.motion.x > 918 && event.motion.x < 1170 && event.motion.y > 363 && event.motion.y < 432);
                    hover[4] = (event.motion.x > 966 && event.motion.x < 1220 && event.motion.y > 715 && event.motion.y < 781);

                  
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        int x = event.button.x;
                        int y = event.button.y;

                        if (x > 603 && x < 855 && y > 256 && y < 321) {
                            int currentVolume = Mix_VolumeMusic(-1) - volumeStep;
                            Mix_VolumeMusic(currentVolume < 0 ? 0 : currentVolume);
                        } else if (x > 917 && x < 1170 && y > 253 && y < 322) {
                            int currentVolume = Mix_VolumeMusic(-1) + volumeStep;
                            Mix_VolumeMusic(currentVolume > MIX_MAX_VOLUME ? MIX_MAX_VOLUME : currentVolume);
                        } else if (x > 603 && x < 858 && y > 367 && y < 430) {
                            screen = SDL_SetVideoMode(1440, 900, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
                        } else if (x > 918 && x < 1170 && y > 363 && y < 432) {
                            screen = SDL_SetVideoMode(1440, 900, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
                        } else if (x > 966 && x < 1220 && y > 715 && y < 781) {
                            running = 0;
                        }
                    }
                    break;
            }
        }

        SDL_BlitSurface(background, NULL, screen, NULL);
        renderButton(screen, diminuer, hover[0]);
        renderButton(screen, augmenter, hover[1]);
        renderButton(screen, normal, hover[2]);
        renderButton(screen, plein_d_ecran, hover[3]);
        renderButton(screen, retour, hover[4]);
        SDL_Flip(screen);
    }

   
    Mix_FreeMusic(music);
    SDL_FreeSurface(background);
    freeButton(&diminuer);
    freeButton(&augmenter);
    freeButton(&normal);
    freeButton(&plein_d_ecran);
    freeButton(&retour);
    SDL_Quit();

    return 0;
}

