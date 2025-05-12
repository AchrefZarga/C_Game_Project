#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <stdio.h>
#include <string.h>
#include "background.h"
#include "menu.h"

#define MAX_SCORES 3

SDL_Surface *btn_quitter[2];
SDL_Surface *btn_retour[2];
SDL_Surface *btn_rejouer[2];
SDL_Rect pos_quitter = {810, 540};
SDL_Rect pos_retour = {340, 540};
SDL_Rect pos_rejouer = {340, 540};

int lancer_une_partie(SDL_Surface *screen, TTF_Font *font) {
    Background bg;
    initBackground(&bg, "background1.jpg");

    SDL_Surface *helpImage = IMG_Load("help.png");
    if (!helpImage) {
        printf("Erreur de chargement de l'image help.png: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Rect helpPos = {10, 50};
    int running = 1, splitScreen = 0, showGuide = 0;
    Uint32 startTime = SDL_GetTicks();
    SDL_Color white = {255, 255, 255};
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = 0;
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE: running = 0; break;
                    case SDLK_SPACE: splitScreen = !splitScreen; break;
                    case SDLK_RIGHT: bg.camera1.x += 10; break;
                    case SDLK_LEFT: bg.camera1.x -= 10; break;
                    case SDLK_UP: bg.camera1.y -= 10; break;
                    case SDLK_DOWN: bg.camera1.y += 10; break;
                    case SDLK_d: if (splitScreen) bg.camera2.x += 10; break;
                    case SDLK_q: if (splitScreen) bg.camera2.x -= 10; break;
                    case SDLK_z: if (splitScreen) bg.camera2.y -= 10; break;
                    case SDLK_s: if (splitScreen) bg.camera2.y += 10; break;
                    case SDLK_RETURN: if (showGuide) showGuide = 0; break;
                    default: break;
                }
            }
            if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                if (event.button.x >= helpPos.x && event.button.x <= helpPos.x + helpImage->w &&
                    event.button.y >= helpPos.y && event.button.y <= helpPos.y + helpImage->h) {
                    showGuide = 1;
                }
            }
        }

        bg.camera1.x = (bg.camera1.x < 0) ? 0 : bg.camera1.x;
        bg.camera1.y = (bg.camera1.y < 0) ? 0 : bg.camera1.y;
        bg.camera1.x = (bg.camera1.x > bg.image->w - bg.camera1.w) ? bg.image->w - bg.camera1.w : bg.camera1.x;
        bg.camera1.y = (bg.camera1.y > bg.image->h - bg.camera1.h) ? bg.image->h - bg.camera1.h : bg.camera1.y;

        bg.camera2.x = (bg.camera2.x < 0) ? 0 : bg.camera2.x;
        bg.camera2.y = (bg.camera2.y < 0) ? 0 : bg.camera2.y;
        bg.camera2.x = (bg.camera2.x > bg.image->w - bg.camera2.w) ? bg.image->w - bg.camera2.w : bg.camera2.x;
        bg.camera2.y = (bg.camera2.y > bg.image->h - bg.camera2.h) ? bg.image->h - bg.camera2.h : bg.camera2.y;

        SDL_FillRect(screen, NULL, 0);

        if (!splitScreen) {
            SDL_BlitSurface(bg.image, &bg.camera1, screen, NULL);
        } else {
            SDL_Rect pos1 = {0, 0};
            SDL_Rect pos2 = {720, 0};
            SDL_BlitSurface(bg.image, &bg.camera1, screen, &pos1);
            SDL_BlitSurface(bg.image, &bg.camera2, screen, &pos2);
        }

        SDL_BlitSurface(helpImage, NULL, screen, &helpPos);

        Uint32 currentTime = SDL_GetTicks();
        Uint32 elapsed = (currentTime - startTime) / 1000;
        char timeText[32];
        sprintf(timeText, "Temps : %d s", elapsed);
        SDL_Surface *textSurface = TTF_RenderText_Solid(font, timeText, white);
        SDL_Rect textPosition = {10, 10};
        SDL_BlitSurface(textSurface, NULL, screen, &textPosition);
        SDL_FreeSurface(textSurface);

        if (showGuide) {
            afficherFenetreGuide(screen, font, white);
        }

        SDL_Flip(screen);
        SDL_Delay(16);

        if (elapsed >= 2) running = 0;
    }

    freeBackground(&bg);
    SDL_FreeSurface(helpImage);
    return (SDL_GetTicks() - startTime) / 1000;
}

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    TTF_Init();
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024);

    SDL_Surface *ecran = SDL_SetVideoMode(1440, 700, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (!ecran) {
        printf("Erreur écran : %s\n", SDL_GetError());
        return 1;
    }

    btn_quitter[0] = IMG_Load("quitternormal.png");
    btn_quitter[1] = IMG_Load("quitterappuye.png");
    btn_retour[0] = IMG_Load("retournernormal.png");
    btn_retour[1] = IMG_Load("retournerappuye.png");
    btn_rejouer[0] = IMG_Load("rejouernormal.png");
    btn_rejouer[1] = IMG_Load("rejouerappuye.png");

    SDL_Surface *result_bg = IMG_Load("score3.png");
    SDL_Surface *etoiles[3];
    etoiles[0] = IMG_Load("etoile1.png");
    etoiles[1] = IMG_Load("etoile2.png");
    etoiles[2] = IMG_Load("etoile3.png");

    if (!btn_quitter[0] || !btn_quitter[1] || !btn_retour[0] || !btn_retour[1] || !btn_rejouer[0] || !btn_rejouer[1] || !result_bg || !etoiles[0] || !etoiles[1] || !etoiles[2]) {
        printf("Erreur chargement images : %s\n", SDL_GetError());
        return 1;
    }

    Mix_Music *victoryMusic = Mix_LoadMUS("victoire.mp3");
    if (!victoryMusic) {
        printf("Erreur chargement musique : %s\n", Mix_GetError());
        return 1;
    }

    int rejouer = 1;
    while (rejouer) {
        rejouer = 0;
        score s;
        init_score(&s);
        int running = 1, partie = 0;
        MeilleurScore top[MAX_SCORES];
        int nb_scores = 0;

        while (running && partie < 3) {
            int score_actuel = lancer_une_partie(ecran, s.font);
            s.score = score_actuel;

            int mode = 1;
            while (mode == 1 && running) {
                afficher(&s, ecran, mode, &running);
                gerer_evenements(&s, ecran, &mode, &running);
            }
            if (!running) break;

            ajouter_score(top, &nb_scores, s.pseudo, s.score);

            int attendre = 1;
            SDL_Event event;
            while (attendre) {
                SDL_BlitSurface(result_bg, NULL, ecran, NULL);
                afficher_resultat(ecran, result_bg, s.font, s.pseudo, s.score);
                SDL_BlitSurface(btn_retour[0], NULL, ecran, &pos_retour);
                SDL_BlitSurface(btn_quitter[0], NULL, ecran, &pos_quitter);
                SDL_Flip(ecran);

                while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT) { attendre = 0; running = 0; }
                    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                        int mx = event.button.x, my = event.button.y;
                         if (mx >= pos_quitter.x && mx <= pos_quitter.x + btn_quitter[0]->w &&
                        my >= pos_quitter.y && my <= pos_quitter.y + btn_quitter[0]->h) {
                        SDL_BlitSurface(btn_quitter[1], NULL, ecran, &pos_quitter);
                        SDL_Flip(ecran);
                        SDL_Delay(200);
                        running = 0; attendre = 0;
                    }
                        if (mx >= pos_retour.x && mx <= pos_retour.x + btn_retour[0]->w &&
                            my >= pos_retour.y && my <= pos_retour.y + btn_retour[0]->h) {
                            SDL_BlitSurface(btn_retour[1], NULL, ecran, &pos_retour);
                            SDL_Flip(ecran);
                            SDL_Delay(200);
                            attendre = 0;
                        }
                    }
                }
            }
            partie++;
        }
if (nb_scores > 0) {
    Mix_PlayMusic(victoryMusic, 1);

    // Nettoyage de l'écran
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));

    // Affiche les meilleurs scores + étoiles (sans flip)
    afficher_meilleurs_scores_fenetre(ecran, top, nb_scores, etoiles, s.font);

    // Affiche les boutons par-dessus
    SDL_BlitSurface(btn_quitter[0], NULL, ecran, &pos_quitter);
    SDL_BlitSurface(btn_rejouer[0], NULL, ecran, &pos_rejouer);

    // Flip une seule fois après tout
    SDL_Flip(ecran);


            int attendre = 1;
            SDL_Event event;
            while (attendre) {
                while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT) { attendre = 0; running = 0; }
                    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                        int mx = event.button.x, my = event.button.y;
                        if (mx >= pos_quitter.x && mx <= pos_quitter.x + btn_quitter[0]->w &&
                            my >= pos_quitter.y && my <= pos_quitter.y + btn_quitter[0]->h) {
                            SDL_BlitSurface(btn_quitter[1], NULL, ecran, &pos_quitter);
                            SDL_Flip(ecran);
                            SDL_Delay(200);
                            attendre = 0;
                            running = 0;
                        }
                        if (mx >= pos_rejouer.x && mx <= pos_rejouer.x + btn_rejouer[0]->w &&
                            my >= pos_rejouer.y && my <= pos_rejouer.y + btn_rejouer[0]->h) {
                            SDL_BlitSurface(btn_rejouer[1], NULL, ecran, &pos_rejouer);
                            SDL_Flip(ecran);
                            SDL_Delay(200);
                            attendre = 0;
                            rejouer = 1;
                        }
                    }
                }
                SDL_Delay(100);
            }
            Mix_HaltMusic();
        }
    }

    for (int i = 0; i < 2; i++) {
        SDL_FreeSurface(btn_quitter[i]);
        SDL_FreeSurface(btn_retour[i]);
        SDL_FreeSurface(btn_rejouer[i]);
    }
    SDL_FreeSurface(result_bg);
    for (int i = 0; i < 3; i++) SDL_FreeSurface(etoiles[i]);
    Mix_FreeMusic(victoryMusic);

    TTF_Quit();
    Mix_CloseAudio();
    SDL_Quit();
    return 0;
}

